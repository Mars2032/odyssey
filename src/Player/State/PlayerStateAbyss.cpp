#include "Player/State/PlayerStateAbyss.h"
#include <Util/PlayerTypeUtil.h>
#include <al/Library/Audio/System/AudioUtil.h>
#include <al/Library/LiveActor/ActorFlagFunction.h>
#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/LiveActor/LiveActor.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>
#include <al/Library/Se/SeFunction.h>

#include "Player/PlayerAnimator.h"
#include "Player/PlayerConst.h"
#include "Player/PlayerRecoverySafetyPoint.h"
#include "Player/State/PlayerStateRecoveryDead.h"

namespace {
NERVE_IMPL(PlayerStateAbyss, Fall);
NERVE_IMPL(PlayerStateAbyss, Recovery);
struct {
    NERVE_MAKE(PlayerStateAbyss, Fall);
    NERVE_MAKE(PlayerStateAbyss, Recovery);
} nrvPlayerStateAbyss;
}  // namespace

PlayerStateAbyss::PlayerStateAbyss(al::LiveActor* parent, const PlayerConst* playerConst, PlayerRecoverySafetyPoint* recoverySafetyPoint,
                                   PlayerColliderHakoniwa* playerCollider, PlayerAnimator* playerAnimator, al::LiveActor* playerModelHolder)
    : ActorStateBase("奈落死", parent), mPlayerConst(playerConst), mPlayerRecoverySafetyPoint(recoverySafetyPoint), mPlayerAnimator(playerAnimator) {
    initNerve(&nrvPlayerStateAbyss.Fall, 1);
    mPlayerStateRecoveryDead =
        new PlayerStateRecoveryDead(parent, recoverySafetyPoint, playerCollider, playerAnimator, playerConst, playerModelHolder);
    al::initNerveState(this, mPlayerStateRecoveryDead, &nrvPlayerStateAbyss.Recovery, "奈落復帰");
}

PlayerStateAbyss::~PlayerStateAbyss() = default;

void PlayerStateAbyss::appear() {
    setDead(false);
    if (mPlayerRecoverySafetyPoint->isValid()) {
        al::offAreaTarget(getParent());
        al::setNerve(this, &nrvPlayerStateAbyss.Recovery);
        return;
    }

    if (rs::isPlayer2D(getParent()))
        mPlayerAnimator->startAnim("Fall");

    al::offAreaTarget(getParent());
    al::setNerve(this, &nrvPlayerStateAbyss.Fall);
}

void PlayerStateAbyss::kill() {
    al::onAreaTarget(getParent());
    al::setNerve(this, &nrvPlayerStateAbyss.Fall);
    setDead(true);
}

void PlayerStateAbyss::exeFall() {
    if (al::isFirstStep(this)) {
        if (!rs::isPlayer3D(getParent())) {
            alSeFunction::startSeFromUpperLayerSeKeeper(getParent(), "FallDown2D");
        } else {
            if (((u8*)mPlayerAnimator)[0x1a2])  // checks if field_1a2 is true
                mPlayerAnimator->endSubAnim();

            mPlayerAnimator->startAnim("DeadFall");
            al::startSe(getParent(), "FallDown");
            al::startSe(getParent(), "vDeadFallDown");
        }
    }
    al::addVelocityToGravityLimit(getParent(), mPlayerConst->getGravityAir(), mPlayerConst->getFallSpeedMax());
}

void PlayerStateAbyss::exeRecovery() {
    if (al::isFirstStep(this)) {
        al::deactivateAudioEventController(getParent());
        al::banAudioEventActivation(getParent());
    }

    if (al::updateNerveState(this)) {
        al::allowAudioEventActivation(getParent());
        al::activateAudioEventController(getParent());
        al::startAndStopBgmInCurPosition(getParent(), false);
        kill();
    }
}

bool PlayerStateAbyss::isRecovery() const {
    return al::isNerve(this, &nrvPlayerStateAbyss.Recovery);
}

bool PlayerStateAbyss::isRecoveryLandFall() const {
    if (!isDead() && al::isNerve(this, &nrvPlayerStateAbyss.Recovery)) {
        return mPlayerStateRecoveryDead->isLandFall();
    }

    return false;
}

void PlayerStateAbyss::prepareRecovery() {
    al::setNerve(this, &nrvPlayerStateAbyss.Recovery);
}