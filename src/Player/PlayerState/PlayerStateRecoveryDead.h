#pragma once

#include <al/Library/Nerve/NerveStateBase.h>
#include <math/seadQuat.h>

class PlayerRecoverySafetyPoint;
class PlayerColliderHakoniwa;
class PlayerAnimator;
class PlayerConst;
class ActorDimensionKeeper;

class PlayerStateRecoveryDead : public al::ActorStateBase {
private:
    PlayerRecoverySafetyPoint* mPlayerRecoverySafetyPoint;
    PlayerColliderHakoniwa* mPlayerColliderHakoniwa;
    PlayerAnimator* mPlayerAnimator;
    const PlayerConst* mPlayerConst;
    al::LiveActor* mPlayerModelHolder;
    f32 field_48;
    f32 field_4c;
    sead::Vector3f mPlayerTrans;
    sead::Vector3f mPlayerGravityInverse;
    sead::Vector3f field_68;
    s32 field_74;
    s32 field_78;
    f32 field_7c;
    sead::Quatf mPlayerQuat;
    sead::Vector3f field_90;
    sead::Vector3f field_9c;
    ActorDimensionKeeper* mDimensionKeeper;
    sead::Vector3f field_b0;
    sead::Vector3f field_bc;

public:
    PlayerStateRecoveryDead(al::LiveActor* parent, PlayerRecoverySafetyPoint* recoverySafetyPoint, PlayerColliderHakoniwa* playerColliderHakoniwa,
                            PlayerAnimator* playerAnimator, const PlayerConst* playerConst, al::LiveActor* playerModelHolder);
    ~PlayerStateRecoveryDead() override;
    void appear() override;
    void kill() override;
    void exeFall();
    void exeRecovery();
    void exeStart();
    bool isLandFall() const;
};