#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

class PlayerConst;
class IUsePlayerCollision;
class PlayerAnimator;
class PlayerActionAirMoveControl;
class HackCap;
class PlayerInput;

class PlayerStateCapCatchPop : public al::ActorStateBase {
private:
    const PlayerConst* mPlayerConst;
    const IUsePlayerCollision* mPlayerCollider;
    PlayerAnimator* mPlayerAnimator;
    PlayerActionAirMoveControl* mPlayerActionAirMoveCtrl;
    HackCap* mHackCap;

public:
    PlayerStateCapCatchPop(al::LiveActor* parent, const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                           const PlayerInput* playerInput, PlayerAnimator* playerAnimator, HackCap* hackCap);
    ~PlayerStateCapCatchPop();
    void appear();
    void exePop();
};
