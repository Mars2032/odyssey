#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/LiveActor/ActorPoseKeeper.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>

#include "Player/PlayerActionAirMoveControl.h"
#include "Player/PlayerConst.h"
#include "Player/PlayerPuppet.h"
#include "Player/PlayerState/PlayerStateBind.h"
#include "Player/PlayerTrigger.h"

namespace {
NERVE_IMPL(PlayerStateBind, Bind);
NERVE_IMPL(PlayerStateBind, EndOnGround);
NERVE_IMPL(PlayerStateBind, EndJump);
NERVE_IMPL(PlayerStateBind, EndCapThrow);
NERVE_IMPL(PlayerStateBind, EndFall);

struct {
    NERVE_MAKE(PlayerStateBind, Bind);
    NERVE_MAKE(PlayerStateBind, EndOnGround);
    NERVE_MAKE(PlayerStateBind, EndJump);
    NERVE_MAKE(PlayerStateBind, EndCapThrow);
    NERVE_MAKE(PlayerStateBind, EndFall);
} nrvPlayerStateBind;
}  // namespace

PlayerStateBind::PlayerStateBind(al::LiveActor* parent, const PlayerConst* playerConst, const PlayerInput* playerInput,
                                 const PlayerPuppet* playerPuppet, const IUsePlayerCollision* playerCollision, PlayerTrigger* playerTrigger)
    : ActorStateBase("バインド", parent), mPlayerTrigger(playerTrigger), mPlayerConst(playerConst), mPlayerPuppet(playerPuppet) {
    mPlayerActionAirMoveCtrl = new PlayerActionAirMoveControl(parent, playerConst, playerInput, playerCollision, false);
    initNerve(&nrvPlayerStateBind.Bind, 0);
}

PlayerStateBind::~PlayerStateBind() = default;

void PlayerStateBind::appear() {
    al::setVelocityZero(getParent());

    if (mPlayerPuppet->isBinding())
        al::setNerve(this, &nrvPlayerStateBind.Bind);
    else if (mPlayerPuppet->isBindEndOnGround())
        al::setNerve(this, &nrvPlayerStateBind.EndOnGround);
    else if (mPlayerPuppet->isBindEndJump())
        al::setNerve(this, &nrvPlayerStateBind.EndJump);
    else if (((u8*)mPlayerPuppet)[0xaa])  // check bool at 0xAA
        al::setNerve(this, &nrvPlayerStateBind.EndCapThrow);
    else
        al::setNerve(this, &nrvPlayerStateBind.EndFall);

    setDead(false);
}

void PlayerStateBind::endBind() {
    if (mPlayerPuppet->isBindEndOnGround())
        return al::setNerve(this, &nrvPlayerStateBind.EndOnGround);

    if (mPlayerPuppet->isBindEndJump())
        return al::setNerve(this, &nrvPlayerStateBind.EndJump);

    if (((u8*)mPlayerPuppet)[0xaa])  // checks bool at 0xAA
        return al::setNerve(this, &nrvPlayerStateBind.EndCapThrow);

    al::setNerve(this, &nrvPlayerStateBind.EndFall);
}

void PlayerStateBind::exeBind() {
    return;
}

void PlayerStateBind::exeEndCapThrow() {
    if (al::isFirstStep(this))
        mPlayerTrigger->set(PlayerTrigger::EActionTrigger::cCollisionExpandCheck);
    al::tryAddVelocityLimit(getParent(), al::getGravity(getParent()) * mPlayerConst->getGravityAir(), mPlayerConst->getFallSpeedMax());
}

void PlayerStateBind::exeEndFall() {
    if (al::isFirstStep(this)) {
        mPlayerTrigger->set(PlayerTrigger::EActionTrigger::cCollisionExpandCheck);
        mPlayerActionAirMoveCtrl->setup(10000.0f, mPlayerConst->getJumpMoveSpeedMin(), 0, al::calcSpeedV(getParent()), mPlayerConst->getJumpGravity(),
                                        0, 0.0f);
    }
    mPlayerActionAirMoveCtrl->update();
}

struct PlayerStateBindUnkStruct {
    sead::Vector3f field_0;
    s32 field_c;
    f32 field_10;
};

void PlayerStateBind::exeEndJump() {
    if (al::isFirstStep(this)) {
        mPlayerTrigger->set(PlayerTrigger::EActionTrigger::cCollisionExpandCheck);
        auto playerPuppetUnkStruct = *reinterpret_cast<PlayerStateBindUnkStruct**>(&((u8*)mPlayerPuppet)[0xc8]);
        al::setVelocity(getParent(), playerPuppetUnkStruct->field_0);
        mPlayerActionAirMoveCtrl->setup(10000.0f, mPlayerConst->getJumpMoveSpeedMin(), 0, al::calcSpeedV(getParent()),
                                        playerPuppetUnkStruct->field_10, playerPuppetUnkStruct->field_c, 0.0f);
    }
    mPlayerActionAirMoveCtrl->update();
}

void PlayerStateBind::exeEndOnGround() {
    if (al::isFirstStep(this))
        mPlayerTrigger->set(PlayerTrigger::EActionTrigger::cCollisionExpandCheck);

    al::tryAddVelocityLimit(getParent(), al::getGravity(getParent()) * mPlayerConst->getGravityAir(), mPlayerConst->getFallSpeedMax());
}

bool PlayerStateBind::isEndAir() const {
    return !al::isNerve(this, &nrvPlayerStateBind.Bind) &&
           (al::isNerve(this, &nrvPlayerStateBind.EndJump) || al::isNerve(this, &nrvPlayerStateBind.EndFall));
}

bool PlayerStateBind::isEndCapThrow() const {
    return !al::isNerve(this, &nrvPlayerStateBind.Bind) && al::isNerve(this, &nrvPlayerStateBind.EndCapThrow);
}

bool PlayerStateBind::isEndOnGround() const {
    return !al::isNerve(this, &nrvPlayerStateBind.Bind) && al::isNerve(this, &nrvPlayerStateBind.EndOnGround);
}

bool PlayerStateBind::isInvalidInput() const {
    if (al::isNerve(this, &nrvPlayerStateBind.EndJump))
        return al::isLessEqualStep(this, (*reinterpret_cast<PlayerStateBindUnkStruct**>(&((u8*)mPlayerPuppet)[0xc8]))->field_c);
    
    return false;
}