#include "Player/State/PlayerStateCameraSubjective.h"

#include <Util/HackTutorialUtil.h>
#include <Util/Math.h>
#include <Util/PlayerTypeUtil.h>
#include <al/Library/Camera/CameraUtil.h>
#include <al/Library/LiveActor/ActorActionFunction.h>
#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/LiveActor/ActorPoseKeeper.h>
#include <al/Library/LiveActor/LiveActor.h>
#include <al/Library/Math/MathAngleUtil.h>
#include <al/Library/Math/MathUtil.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>
#include <al/Library/PostProcessing/CameraBlurController.h>
#include <al/Library/Se/SeFunction.h>

#include "Player/IPlayerModelChanger.h"
#include "Player/PlayerAnimator.h"
#include "Player/PlayerCarryKeeper.h"
#include "Player/PlayerConst.h"
#include "Player/PlayerInput.h"
#include "Util/NpcEventFlowUtil.h"

namespace {
NERVE_IMPL(PlayerStateCameraSubjective, Wait);
NERVE_IMPL(PlayerStateCameraSubjective, Start);
NERVE_IMPL(PlayerStateCameraSubjective, End);

NERVE_MAKE(PlayerStateCameraSubjective, Wait);
NERVE_MAKE(PlayerStateCameraSubjective, Start);
NERVE_MAKE(PlayerStateCameraSubjective, End);
}  // namespace

PlayerStateCameraSubjective::PlayerStateCameraSubjective(al::LiveActor* parent, al::CameraTicket* camera, IPlayerModelChanger* modelChanger,
                                                         PlayerCarryKeeper* carryKeeper, PlayerAnimator* playerAnimator,
                                                         const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                                                         const PlayerInput* playerInput)
    : ActorStateBase("主観カメラ", parent), mPlayerConst(playerConst), mPlayerCollider(playerCollision), mPlayerInput(playerInput),
      mCameraSubjective(camera), mPlayerModelChanger(modelChanger), mPlayerCarryKeeper(carryKeeper), mPlayerAnimator(playerAnimator) {
    al::setCameraInterpoleStep(camera, 10);
    initNerve(&Wait, 0);
}
PlayerStateCameraSubjective::~PlayerStateCameraSubjective() = default;

void PlayerStateCameraSubjective::appear() {
    setDead(false);
    mIsInterruptByDemo = false;
    alSeFunction::startListenerPoser(getParent(), "カメラ位置", 30);
    al::setNerve(this, &Start);
}

void PlayerStateCameraSubjective::end() {
    auto camera = mCameraSubjective;
    auto parent = getParent();
    rs::tryClosePlayerCameraSubjectiveTutorial(parent);
    al::endCamera(parent, camera, 10, false);
}

void PlayerStateCameraSubjective::kill() {
    if (al::isActiveCamera(mCameraSubjective))
        end();

    if (!mIsInterruptByDemo)
        mPlayerModelChanger->showModel();

    if (mPlayerCarryKeeper->isCarry())
        mPlayerCarryKeeper->endCameraSubjective();

    alSeFunction::endListenerPoser(getParent(), "カメラ位置", 0);
    setDead(true);
}

void PlayerStateCameraSubjective::control() {
    rs::waitGround(getParent(), mPlayerCollider, mPlayerConst->getGravity(), mPlayerConst->getFallSpeedMax(), mPlayerConst->getSlerpQuatRate(),
                   mPlayerConst->getWaitPoseDegreeMax());
}

void PlayerStateCameraSubjective::exeWait() {
    if (al::isFirstStep(this)) {
        mPlayerModelChanger->hideModel();
        if (mPlayerCarryKeeper->isCarry())
            mPlayerCarryKeeper->startCameraSubjective();

        rs::tryAppearPlayerCameraSubjectiveTutorial(getParent());
        mPlayerAnimator->startAnim("Wait");
    }

    faceToCameraDir();
    if (mPlayerInput->isTriggerCameraSubjective())
        al::setNerve(this, &End);
}

void PlayerStateCameraSubjective::exeStart() {
    auto parent = getParent();
    if (al::isFirstStep(this)) {
        al::startCamera(parent, mCameraSubjective, -1);
        mConvergeRate = 0.0f;
        alCameraBlurFunction::setCameraBlurName(parent, "Subjective");
        al::startHitReaction(parent, "主観カメラ起動");
    }
    faceToCameraDir();
    if (!al::isActiveCameraInterpole(parent, 0))
        al::setNerve(this, &Wait);
}

void PlayerStateCameraSubjective::exeEnd() {
    if (al::isFirstStep(this)) {
        auto parent = getParent();
        sead::Vector3f cameraLookDir = {0.0f, 0.0f, 0.0f};
        al::calcCameraLookDir(&cameraLookDir, parent, 0);
        al::verticalizeVec(&cameraLookDir, al::getGravity(parent), cameraLookDir);
        if (al::tryNormalizeOrZero(&cameraLookDir))
            al::faceToDirection(parent, cameraLookDir);
        end();
        al::startHitReaction(parent, "主観カメラ終了");
    }

    if (!al::isLessStep(this, 10)) {
        alCameraBlurFunction::resetCameraBlurName(getParent());
        kill();
    }
}

void PlayerStateCameraSubjective::faceToCameraDir() {
    mConvergeRate = al::converge(mConvergeRate, 15, 1);
    auto parent = getParent();
    sead::Vector3f groundNormal = {0.0f, 0.0f, 0.0f};
    rs::calcGroundNormalOrUpDir(&groundNormal, parent, mPlayerCollider);
    sead::Vector3f up = {0.0f, 0.0f, 0.0f};
    if (!rs::isPlayerInWater(parent))
        up.e = groundNormal.e;  // hacky match
    else
        up = -al::getGravity(parent);
    sead::Vector3f lookDir = {0.0f, 0.0f, 0.0f};
    al::calcCameraLookDir(&lookDir, parent, 0);
    al::verticalizeVec(&lookDir, up, lookDir);

    if (al::tryNormalizeOrZero(&lookDir)) {
        f32 rate = sead::Mathf::clampMax(mConvergeRate / 15.0f, 1.0f);
        sead::Vector3f front = {0.0f, 0.0f, 0.0f};
        al::calcFrontDir(&front, parent);
        al::turnVecToVecRate(&front, front, lookDir, rate);
        rs::slerpUpFront(parent, up, front, mPlayerConst->getSlerpQuatRate(), mPlayerConst->getWaitPoseDegreeMax());
    }
    auto grnd = groundNormal;
    sead::Vector3f velocity = -(grnd * mPlayerConst->getGravity());  // these 2 lines are weird... maybe a function call? but i can't find one

    al::setVelocity(parent, velocity);
}

void PlayerStateCameraSubjective::interruptByDemo() {
    if (al::isActiveCamera(mCameraSubjective)) {
        end();
        mPlayerAnimator->resetModelAlpha();
        mPlayerModelChanger->showModel();
        mIsInterruptByDemo = true;
    }
}

bool PlayerStateCameraSubjective::isStateActiveCamera() const {
    if (isDead())
        return false;

    return al::isNerve(this, &Wait);
}