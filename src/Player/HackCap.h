#pragma once

#include <al/Library/LiveActor/LiveActor.h>

class PlayerInput;
class PlayerAreaChecker;
class PlayerWallActionHistory;
class PlayerCapActionHistory;
class PlayerEyeSensorHitHolder;
class PlayerSeparateCapFlag;
class IUsePlayerCollision;
class IUsePlayerHeightCheck;
class PlayerWetControl;
class PlayerWetControl;
class HackCapJudgePreInputSeparateThrow;
class HackCapJudgePreInputSeparateJump;
class CapTargetInfo;

class HackCap : public al::LiveActor {
public:
    enum class SwingHandType { Left, Right };

    HackCap(const al::LiveActor*, const char*, const PlayerInput*, const PlayerAreaChecker*, const PlayerWallActionHistory*,
            const PlayerCapActionHistory*, const PlayerEyeSensorHitHolder*, const PlayerSeparateCapFlag*, const IUsePlayerCollision*,
            const IUsePlayerHeightCheck*, const PlayerWetControl*, const PlayerWetControl*, HackCapJudgePreInputSeparateThrow*,
            HackCapJudgePreInputSeparateJump*);

    void init(const al::ActorInitInfo&);
    void hide(bool);
    void movement();
    void updateShadowMaskOffset();
    void control();
    void updateTargetLayout();
    void updateCollider();
    void updateFrameOutLayout();
    void attackSpin(al::HitSensor*, al::HitSensor*, float);
    void prepareLockOn(al::HitSensor*);
    void sendMsgStartHack(al::HitSensor*);
    void receiveRequestTransferHack(al::HitSensor*, al::HitSensor*);
    void startThrowSeparatePlayHack(al::HitSensor*, const sead::Vector3f&, const sead::Vector3f&, float);
    void startHack();
    void emitHackStartEffect();
    void noticeHackMarioEnter();
    void noticeHackDemoPuppetableEnd();
    void recordHack();
    void addHackStartDemo();
    void addLockOnKeepDemo();
    void syncHackDamageVisibility(bool);
    void endHack();
    void startSpinAttack(const char*);
    void startThrow(bool, const sead::Vector3f&, const sead::Vector3f&, float, const sead::Vector2f&, const sead::Vector2f&, const sead::Vector3f&,
                    bool, const sead::Vector3f&, SwingHandType, bool, float, int);

    void startThrowSeparatePlay(const sead::Vector3f&, const sead::Vector3f&, float, bool);
    void startThrowSeparatePlayJump(const sead::Vector3f&, const sead::Vector3f&, float);
    void startCatch(const char*, bool, const sead::Vector3f&);
    void forcePutOn();
    void forceHack(al::HitSensor*, const CapTargetInfo*);
    void resetLockOnParam();
    void setupStartLockOn();
    void cancelCapState();
    void requestReturn(bool*);
    void tryReturn(bool, bool*);
    void updateCapPose();
    void followTarget();
    void syncPuppetSilhouette();
    void recordCapJump(PlayerWallActionHistory*);
    void getFlyingSpeedMax();
    void getThrowSpeed();
    void requestLockOnHitReaction(const CapTargetInfo*, const char*);
    void startPuppet();
    void endPuppet();
    void hidePuppetCap();
    void showPuppetCap();
    void hidePuppetCapSilhouette();
    void showPuppetCapSilhouette();
    void startPuppetCheckpointWarp();
    void startHackShineGetDemo();
    void endHackThrowAndReturnHack();
    void endHackShineGetDemo();
    void calcHackFollowTrans(sead::Vector3f*, bool);
    void makeFollowMtx(sead::Matrix34f*);
    void updateCapEyeShowHide(bool, int);
    void activateInvincibleEffect();
    void syncInvincibleEffect(bool);
    void updateSeparateMode(const PlayerSeparateCapFlag*);
    void startRescuePlayer();
    void prepareCooperateThrow();
    void requestForceFollowSeparateHide();
    void calcSeparateHideSpeedH(const sead::Vector3f&);
    void updateModelAlphaForSnapShot();
    void getPadRumblePort();
    void updateThrowJoint();
    void setupThrowStart();
    void getThrowHeight();
    void checkEnableThrowStartSpace(sead::Vector3f*, sead::Vector3f*, sead::Vector3f*, const sead::Vector3f&, float, float, bool,
                                    const sead::Vector3f&);
    void updateWaterArea();
    void getThrowRange();
    void getThrowBrakeTime();
    void startThrowCapEyeThrowAction();
    void tryCollideReflectReaction();
    void tryCollideWallReaction();
    void changeThrowParamInWater(int, bool);
    void addCurveOffset();
    void tryAppendAttack();
    void tryCollideWallReactionSpiral();
    void endThrowSpiral();
    void tryCollideWallReactionReflect();
    void tryCollideWallReactionRollingGround();
    void rollingGround();
    void tryChangeSeparateThrow();
    void getThrowBackSpeed();
    void updateLavaSurfaceMove();
    void tryCollideWallReactionStay();
    void getThrowStayTime();
    void getThrowStayTimeMax();
    void getThrowSpeedAppend();
    void getThrowRangeAppend();
    void tryCollideWallLockOn();
    void endHackThrowAndReturnHackOrHide();
    void clearThrowType();
    void calcReturnTargetPos(sead::Vector3f*);
    void attackSensor(al::HitSensor*, al::HitSensor*);
    void stayRollingOrReflect();
    bool receiveMsg(const al::SensorMsg*, al::HitSensor*, al::HitSensor*);
    void endMove();
    void prepareTransferLockOn(al::HitSensor*);
    void collideThrowStartArrow(al::HitSensor*, const sead::Vector3f&, const sead::Vector3f&, const sead::Vector3f&);
    void trySendAttackCollideAndReaction(bool*);
    void stayWallHit();
    void endHackThrow();
    bool isFlying() const;
    bool isNoPutOnHide() const;
    bool isEnableThrow() const;
    bool isEnableSpinAttack() const;
    bool isSpinAttack() const;
    bool isEnableRescuePlayer() const;
    bool isRescuePlayer() const;
    bool isEnableHackThrow(bool*) const;
    bool isSeparateHipDropLand() const;
    bool isSeparateHide() const;
    bool isSeparateThrowFlying() const;
    bool isEnableThrowSeparate() const;
    bool isHoldInputKeepLockOn() const;
    bool isRequestableReturn() const;
    bool isLockOnEnableHackTarget() const;
    bool isWaitHackLockOn() const;
    bool isCatched() const;
    bool isHide() const;
    bool isPutOn() const;
    bool isLockOnInterpolate() const;
    bool isEnablePreInput() const;
    bool isForceCapTouchJump() const;
    bool isHackInvalidSeparatePlay() const;
    bool isHoldSpinCapStay() const;
    bool isThrowTypeSpiral() const;
    bool isThrowTypeRolling() const;
    bool isEnableHackThrowAutoCatch() const;
    bool isEnableCapTouchJumpInput() const;
    void exeLockOn();
    void exeHack();
    void exeSpinAttack();
    void exeCatch();
    void exeTrample();
    void exeTrampleLockOn();
    void exeRescue();
    void exeHide();
    void exeThrowStart();
    void exeThrow();
    void exeThrowBrake();
    void exeThrowSpiral();
    void exeThrowTornado();
    void exeThrowRolling();
    void exeThrowRollingBrake();
    void exeThrowStay();
    void exeThrowAppend();
    void exeRebound();
    void exeReturn();
    void exeBlow();
};