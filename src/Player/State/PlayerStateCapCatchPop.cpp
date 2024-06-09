#include "Player/State/PlayerStateCapCatchPop.h"

#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>

#include "Player/Action/PlayerActionAirMoveControl.h"
#include "Player/HackCap.h"
#include "Player/PlayerAnimator.h"
#include "Player/PlayerConst.h"

namespace {
NERVE_IMPL(PlayerStateCapCatchPop, Pop);
NERVE_MAKE(PlayerStateCapCatchPop, Pop);
}  // namespace

PlayerStateCapCatchPop::PlayerStateCapCatchPop(al::LiveActor* parent, const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                                               const PlayerInput* playerInput, PlayerAnimator* playerAnimator, HackCap* hackCap)
    : ActorStateBase("帽子キャッチ浮き", parent), mPlayerConst(playerConst), mPlayerCollider(playerCollision), mPlayerAnimator(playerAnimator),
      mHackCap(hackCap) {
    mPlayerActionAirMoveCtrl = new PlayerActionAirMoveControl(parent, playerConst, playerInput, playerCollision, false);
    initNerve(&Pop, 0);
}

PlayerStateCapCatchPop::~PlayerStateCapCatchPop() = default;

void PlayerStateCapCatchPop::appear() {
    setDead(false);
    al::setNerve(this, &Pop);
}

void PlayerStateCapCatchPop::exePop() {
    if (al::isFirstStep(this)) {
        if (((u8*)mPlayerAnimator)[0x1a2])  // checks if field_1a2 is true
            mPlayerAnimator->endSubAnim();

        mPlayerAnimator->startAnim("JumpCapCatchAir");
        mHackCap->startCatch("JumpCapCatch", false, sead::Vector3f::zero);
        mPlayerActionAirMoveCtrl->setup(mPlayerConst->getSpinAirSpeedMax(), mPlayerConst->getSpinAirSpeedMax(), 0,
                                        mPlayerConst->getCapCatchPopPower(), mPlayerConst->getCapCatchPopGravity(), 0, 0.0f);
    }
    mPlayerActionAirMoveCtrl->update();
    if (mPlayerAnimator->isAnimEnd() && !al::isLessStep(this, 30))
        kill();
}