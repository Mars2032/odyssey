#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

class PlayerConst;
class PlayerRecoverySafetyPoint;
class PlayerAnimator;
class PlayerStateRecoveryDead;
class PlayerColliderHakoniwa;

class PlayerStateAbyss : public al::ActorStateBase {
private:
    const PlayerConst* mPlayerConst;
    PlayerRecoverySafetyPoint* mPlayerRecoverySafetyPoint;
    PlayerAnimator* mPlayerAnimator;
    PlayerStateRecoveryDead* mPlayerStateRecoveryDead = nullptr;

public:
    PlayerStateAbyss(al::LiveActor* parent, const PlayerConst* playerConst, PlayerRecoverySafetyPoint* recoverySafetyPoint,
                     PlayerColliderHakoniwa* playerCollider, PlayerAnimator* playerAnimator, al::LiveActor* playerModelHolder);
    ~PlayerStateAbyss() override;
    void appear() override;
    void kill() override;
    void exeFall();
    void exeRecovery();
    bool isRecovery() const;
    bool isRecoveryLandFall() const;
    void prepareRecovery();
};
