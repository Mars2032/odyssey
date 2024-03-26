#pragma once

#include "Player/IUsePlayerPuppet.h"

namespace al {
class LiveActor;
class AreaObj;
}  // namespace al

class HackCap;
class PlayerAnimator;
class IUsePlayerCollision;
class ActorDimensionKeeper;
class IPlayerModelChanger;
class WorldEndBorderKeeper;
class PlayerCounterForceRun;
class PlayerDamageKeeper;
class PlayerEffect;
class PlayerInput;
class PlayerConst;

class PlayerPuppet : public IUsePlayerPuppet {
private:
    // missing member fields
public:
    PlayerPuppet(al::LiveActor* parent, HackCap* hackCap, PlayerAnimator* playerAnimator, IUsePlayerCollision* playerCollision,
                 ActorDimensionKeeper* dimensionKeeper, IPlayerModelChanger* modelChanger, WorldEndBorderKeeper* worldEndBorderKeeper,
                 PlayerCounterForceRun* playerCounterForceRun, PlayerDamageKeeper* playerDamageKeeper, PlayerEffect* playerEffect,
                 const PlayerInput* playerInput, const PlayerConst* playerConst);

    void start(al::HitSensor*, al::HitSensor*) override;
    void end() override;
    void cancel() override;
    void setTrans(const sead::Vector3f&) override;
    void setPose(const sead::Quatf&) override;
    void setVelocity(const sead::Vector3f&) override;
    void resetPosition(const sead::Vector3f&) override;
    sead::Vector3f& getTrans() const override;
    sead::Vector3f& getVelocity() const override;
    sead::Vector3f& getGravity() const override;
    void calcFront(sead::Vector3f*) const override;
    void calcUp(sead::Vector3f*) const override;
    void startAction(sead::SafeString const&) const override;
    bool isActionEnd() const override;
    bool isActionPlaying(char const*) const override;
    void setAnimRate(float) const override;
    int getAnimFrameMax() const override;
    void hide() override;
    void show() override;
    bool isHidden() const override;
    void hideSilhouette() override;
    void showSilhouette() override;
    void hideShadow() override;
    void showShadow() override;
    void requestDamage() override;
    void clearRequestDamage() override;
    bool isRequestDamage() const override;
    void setBindEndOnGround() override;
    bool isBindEndOnGround() const override;
    void setBindEndJump(const sead::Vector3f&, int) override;
    bool isBindEndJump() const override;
    void validateCollisionCheck() override;
    void invalidateCollisionCheck() override;
    bool isValidCollisionCheck() override;
    bool isCollidedGround() override;
    sead::Vector3f* getCollidedGroundNormal() override;
    void validateSensor() override;
    void invalidateSensor() override;

    void endKeepOn2D();
    bool isBinding() const;
    bool isNoCollide() const;
    void keepOn2D();
    void requestUpdateRecoveryInfo(bool, bool, const sead::Vector3f&, const sead::Vector3f&, const al::AreaObj*);
    void setBindEndWallJump(const sead::Vector3f&, int);
    void startPlayerHitReaction(const char*);
    void tryUpdateRecoveryInfo(bool*, bool*, sead::Vector3f*, sead::Vector3f*, const al::AreaObj**);  // might not be void return type
    void validate2D();
};