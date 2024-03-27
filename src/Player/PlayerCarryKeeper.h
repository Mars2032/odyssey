#pragma once

#include <al/Library/Nerve/NerveExecutor.h>

namespace al {
class LiveActor;
class HitSensor;
}  // namespace al

class PlayerAnimator;
class IPlayerModelChanger;
class IUsePlayerCeilingCheck;
class PlayerJointParamHandLegAngle;
class IUsePlayerCollision;
class PlayerPushReceiver;

class PlayerCarryKeeper : public al::NerveExecutor {
private:
public:
    PlayerCarryKeeper(const al::LiveActor*, al::HitSensor*, PlayerAnimator*, const IPlayerModelChanger*, const IUsePlayerCeilingCheck*,
                      PlayerJointParamHandLegAngle*);
    void update();
    void updateCollideLockUp(const IUsePlayerCollision*, const PlayerPushReceiver*);
    void startCarry(al::HitSensor*);
    void startThrow(bool);
    void startCancelAndRelease();
    void startRelease();
    void startReleaseDemo();
    void startReleaseDamage();
    void startReleaseDead();
    void startDemoKeepCarry();
    void startDemoShineGet();
    void endDemoShineGet();
    void getCarryStartAnimName() const;
    void startCameraSubjective();
    void endCameraSubjective();
    void sendPlayerWarp();
    bool isCarry() const;
    bool isCarryWallKeep() const;
    bool isCarryFront() const;
    bool isCarryUp() const;
    bool isThrow() const;
    bool isThrowHandR() const;
    void getCarryThrowAnimName() const;
    bool isThrowHold() const;
    void getThrowReleaseFrame() const;
    bool isThrowRelease() const;
    void exeWait();
    void exeStart();
    void updateHandJointAngle();
    void exeCarry();
    void getCarryAnimName() const;
    void exeThrow();
    void exeRelease();
    ~PlayerCarryKeeper();
};