#include "Scene/StageSceneState/StageSceneStateSnapShot.h"
#include <al/Library/Camera/CameraUtil.h>
#include <al/Library/Draw/GraphicsFunction.h>
#include <al/Library/Effect/EffectSystem.h>
#include <al/Library/Framework/GameFrameworkNx.h>
#include <al/Library/LiveActor/LiveActorKit.h>
#include <al/Library/Math/MathUtil.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>
#include <al/Library/Play/Layout/SimpleLayoutAppearWaitEnd.h>
#include <al/Library/Player/PlayerHolder.h>
#include <al/Library/Scene/Scene.h>
#include <al/Library/Scene/SceneHolder.h>
#include <al/Library/Se/SeFunction.h>
#include "Layout/ControllerGuideSnapShotCtrl.h"
#include "Npc/NpcEventDirector.h"
#include "Scene/SceneAudioSystemPauseController.h"
#include "Scene/SceneFunction.h"
#include "System/Application.h"
#include "Util/InputSeparator.h"

namespace {
NERVE_IMPL(StageSceneStateSnapShot, Wait);
struct {
    NERVE_MAKE(StageSceneStateSnapShot, Wait);
} nrvStageSceneStateSnapShot;
}  // namespace

namespace rs {
bool isTriggerSnapShotMode(const al::IUseSceneObjHolder*);
bool isHelpAmiiboMode(const al::IUseSceneObjHolder*);
bool isPlayerSafetyPointRecovery(const al::LiveActor*);
bool isTriggerUiCancel(const al::IUseSceneObjHolder*);
bool isModeE3MovieRom();
bool isModeMovieRom();
}  // namespace rs

StageSceneStateSnapShot::StageSceneStateSnapShot(const char* stateName, al::Scene* parent, ControllerGuideSnapShotCtrl* snapShotCtrl,
                                                 SceneAudioSystemPauseController* audioController, InputSeparator* inputSeparator,
                                                 NpcEventDirector* npcEventDirector)
    : NerveStateBase(stateName), mNpcEventDirector(npcEventDirector), mParent(parent), mControllerGuideSnapShotCtrl(snapShotCtrl),
      mAudioPauseController(audioController), mInputSeparator(inputSeparator) {
    initNerve(&nrvStageSceneStateSnapShot.Wait, 0);
}

void StageSceneStateSnapShot::appear() {
    setDead(false);
    al::setNerve(this, &nrvStageSceneStateSnapShot.Wait);
}

void StageSceneStateSnapShot::kill() {
    setDead(true);
}

bool StageSceneStateSnapShot::tryStart() {
    if (rs::isTriggerSnapShotMode(mParent) && !rs::isHelpAmiiboMode(mParent))
        return true;
    return false;
    //    return rs::isTriggerSnapShotMode(mParent) && !rs::isHelpAmiiboMode(mParent);      <-- does not match
}

void StageSceneStateSnapShot::exeWait() {
    if (al::isFirstStep(this)) {
        al::pausePadRumble(mParent);
        mAudioPauseController->pause(false);
        al::LiveActor* player = al::tryFindAlivePlayerActorFirst(al::getScenePlayerHolder(mParent));
        al::startCameraSnapShotMode(mParent, player && rs::isPlayerSafetyPointRecovery(player));
        al::validatePostProcessingFilter(mParent);
        alGraphicsFunction::forceGraphicsQualityModeSnapShot(mParent);
        alGraphicsFunction::setRainUpdateFlag(mParent, false);
        alGraphicsFunction::setFogNoiseUpdateFlag(mParent, false);
        sead::DynamicCast<al::GameFrameworkNx, sead::GameFrameworkNx>(Application::instance()->getGameFramework())->setVBlankWaitInterval(2);
        mControllerGuideSnapShotCtrl->start();
        ScenePlayerFunction::startSnapShotMode(mParent);
        SceneEventNotifyFunction::notifySnapShotModeOn(mParent);
        if (mNpcEventDirector)
            mNpcEventDirector->killAllBalloonForSnapShotMode();
        alSeFunction::startSeFromUpperLayerSeKeeper(mParent, "enterSnapShotMode");
    }

    mControllerGuideSnapShotCtrl->update();
    mInputSeparator->updateForSnapShotMode();

    if (mInputSeparator->isTriggerIncrementPostProcessingFilterPreset()) {
        al::incrementPostProcessingFilterPreset(mParent);
        al::startSe(mControllerGuideSnapShotCtrl->getSnapShotFrameLayout(),
                    al::getPostProcessingFilterPresetId(mParent) == 0 ? "FilterSelectNone" : "FilterSelectR");
    }
    if (mInputSeparator->isTriggerDecrementPostProcessingFilterPreset()) {
        al::decrementPostProcessingFilterPreset(mParent);
        al::startSe(mControllerGuideSnapShotCtrl->getSnapShotFrameLayout(),
                    al::getPostProcessingFilterPresetId(mParent) == 0 ? "FilterSelectNone" : "FilterSelectL");
    }
    s32 id = al::getPostProcessingFilterPresetId(mParent);
    mControllerGuideSnapShotCtrl->setFilterName(id);
    mParent->getLiveActorKit()->getEffectSystem()->setIsUpdateKit(true);
    al::updateKitListPrev(mParent);
    al::updateKitList(mParent, "カメラ");                // camera
    al::updateKitList(mParent, "クリッピング");          // clipping
    al::updateKitTable(mParent, "スナップショット");     // snap shot
    al::updateKitList(mParent, "シャドウマスク");        // shadow mask
    al::updateKitList(mParent, "グラフィックス要求者");  // graphics requester
    al::updateKitList(mParent, "２Ｄ（ポーズ無視）");    // 2D (ignore pose)
    ScenePlayerFunction::updatePlayerDither(mParent);
    rs::updateKitListPostSnapShot(mParent);
    mParent->getLiveActorKit()->getEffectSystem()->setIsUpdateKit(false);
    sead::Vector3f cameraUp = sead::Vector3f::ey;
    al::calcCameraUpDir(&cameraUp, mParent, 0);
    sead::Vector3f cameraLook = sead::Vector3f::ez;
    al::calcCameraLookDir(&cameraLook, mParent, 0);
    sead::Vector3f cameraSide;
    cameraSide.setCross(cameraLook, sead::Vector3f::ey);
    al::tryNormalizeOrZero(&cameraSide);
    sead::Vector3f cameraAngledUp;
    cameraAngledUp.setCross(cameraSide, cameraLook);
    al::tryNormalizeOrZero(&cameraAngledUp);

    sead::Vector3f sphereMap = sead::Vector3f(0.0f, 0.0f,
                                              (!al::isNear(cameraUp, cameraLook, 0.001f) && !al::isNear(cameraAngledUp, cameraLook, 0.001f)) ?
                                                  al::calcAngleOnPlaneDegree(cameraAngledUp, cameraUp, cameraLook) :
                                                  0.0f);

    alGraphicsFunction::setSphereMapUpdateEveryFrame(mParent, sphereMap);
    if (!mInputSeparator->isTriggerSnapShotMode() && !rs::isTriggerUiCancel(mParent))
        return;
    al::endPausePadRumble(mParent);
    mControllerGuideSnapShotCtrl->end();
    al::endCameraSnapShotMode(mParent);
    mAudioPauseController->resume(1);
    al::invalidatePostProcessingFilter(mParent);
    alGraphicsFunction::unforceGraphicsQualityMode(mParent);
    alGraphicsFunction::setRainUpdateFlag(mParent, true);
    alGraphicsFunction::setFogNoiseUpdateFlag(mParent, true);
    alGraphicsFunction::setSphereMapUpdateEveryFrame(mParent, sead::Vector3f::zero);
    SceneEventNotifyFunction::notifySnapShotModeOff(mParent);

    if (!rs::isModeE3MovieRom() && !rs::isModeMovieRom()) {
        sead::DynamicCast<al::GameFrameworkNx, sead::GameFrameworkNx>(Application::instance()->getGameFramework())->setVBlankWaitInterval(1);
    }

    ScenePlayerFunction::endSnapShotMode(mParent);
    kill();
}