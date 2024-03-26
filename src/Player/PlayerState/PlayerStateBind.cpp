#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>

#include "Player/PlayerActionAirMoveControl.h"
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
        al::setNerve(this, &nrvPlayerStateBind.EndOnGround);
    else if (mPlayerPuppet->isBindEndJump())
        al::setNerve(this, &nrvPlayerStateBind.EndJump);
    else if (((u8*)mPlayerPuppet)[0xaa])  // checks bool at 0xAA
        al::setNerve(this, &nrvPlayerStateBind.EndCapThrow);
    else
        al::setNerve(this, &nrvPlayerStateBind.EndFall);
}

void PlayerStateBind::exeBind() {
    return;
}

void PlayerStateBind::exeEndCapThrow() {}