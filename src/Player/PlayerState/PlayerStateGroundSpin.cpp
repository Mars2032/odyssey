#include "Player/PlayerState/PlayerStateGroundSpin.h"
#include "Player/PlayerActionGroundMoveControl.h"
#include "Player/PlayerInput.h"
#include "Player/PlayerAnimator.h"
#include "Player/PlayerConst.h"
#include "Util/Math.h"
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>
#include <al/Library/Math/MathUtil.h>
#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/LiveActor/ActorPoseKeeper.h>

namespace {
    NERVE_IMPL(PlayerStateGroundSpin, GroundSpin);
    struct {
        NERVE_MAKE(PlayerStateGroundSpin, GroundSpin);
    } nrvPlayerStateGroundSpin;
}

PlayerStateGroundSpin::PlayerStateGroundSpin(al::LiveActor *parent, const IUsePlayerCollision *collision,
                                             const PlayerInput *input, const PlayerConst *playerConst,
                                             PlayerAnimator *animator) : ActorStateBase("地上スピン", parent),
                                                                         mCollision(collision), mPlayerInput(input), mPlayerConst(playerConst),
                                                                         mPlayerAnimator(animator) {
    mIsSpinClockwise = false;
    mGroundMoveCtrl = new PlayerActionGroundMoveControl(parent, playerConst, input, collision);
    mGroundMoveCtrl->set_field_c4();
    mGroundMoveCtrl->setup(0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 0);
    initNerve(&nrvPlayerStateGroundSpin.GroundSpin, 0);
}

void PlayerStateGroundSpin::appear() {
    setDead(false);
    mGroundMoveCtrl->appear();
    mIsSpinClockwise = mPlayerInput->isSpinClockwise();
    al::setNerve(this, &nrvPlayerStateGroundSpin.GroundSpin);
}

void PlayerStateGroundSpin::exeGroundSpin() {
    if (al::isFirstStep(this)) {
        mPlayerAnimator->startAnim(mIsSpinClockwise ? "SpinGroundR" : "SpinGroundL");
    }
    sead::Vector3f velocity = {0.0f, 0.0f, 0.0f};
    mGroundMoveCtrl->updateNormalAndSnap(&velocity);
    sead::Vector3f input = {0.0f, 0.0f, 0.0f};
    mPlayerInput->calcMoveInput(&input, mGroundMoveCtrl->getGroundNormal());
    velocity *= mPlayerConst->getGroundSpinBrakeRate();
    float velocityLength = velocity.length();
    float grndSpinMax = mPlayerConst->getGroundSpinMoveSpeedMax();
    velocityLength = velocityLength > grndSpinMax ? velocityLength : grndSpinMax;
    velocity += mPlayerConst->getGroundSpinAccelRate() * input;
    al::limitLength(&velocity, velocity, velocityLength);
    al::setVelocity(getActor(), velocity - mGroundMoveCtrl->getGroundNormal() * mPlayerConst->getGravityMove());
    sead::Vector3f frontDir = {0.0f, 0.0f, 0.0f};
    if (!al::tryNormalizeOrZero(&frontDir, velocity)) {
        al::calcFrontDir(&frontDir, getActor());
    }
    rs::slerpUpFront(getActor(), sead::Vector3f::ey, frontDir, mPlayerConst->getSlerpQuatRate(), 0.0);
    if (!al::isLessStep(this, mPlayerConst->getGroundSpinFrame())) {
        kill();
    }

}