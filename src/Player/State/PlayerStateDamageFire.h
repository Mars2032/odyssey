#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

class PlayerConst;
class IUsePlayerCollision;
class PlayerInput;
class PlayerActionAirMoveControl;
class PlayerActionGroundMoveControl;
class PlayerAnimator;
class IJudge;

class PlayerStateDamageFire : public al::ActorStateBase {
private:
    const PlayerConst* mPlayerConst;
    const IUsePlayerCollision* mPlayerCollider;
    const PlayerInput* mPlayerInput;
    PlayerActionAirMoveControl* mPlayerActionAirMoveCtrl = nullptr;
    PlayerActionGroundMoveControl* mPlayerActionGroundMoveCtrl = nullptr;
    PlayerAnimator* mPlayerAnimator;
    IJudge* mPlayerJudgeSpeedCheckFall;
    bool mIsDamageFireGround = false;
    bool mIsDamageFireWall = false;
    bool mIsDamageFireCeiling = false;
    bool field_5b;
    s32 mDamageFireTimer = 0;
    s32 mFireRunBrakeFrame = 0;

public:
    PlayerStateDamageFire(al::LiveActor* parent, const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                          const PlayerInput* playerInput, PlayerAnimator* playerAnimator, IJudge* playerJudgeSpeedCheckFall);
    ~PlayerStateDamageFire();
    void appear();
    void control();
    bool isEndFirstLand() const;
    bool isEnableJump() const;
    bool isEnablePeachAmiibo() const;
    s32 getEnableCancelCollisionSnapFrame() const;
    void exeJump();
    void exeJump2nd();
    void exeRun();
    void exeFall();
    void exeDead();
};
