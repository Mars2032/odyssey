#pragma once

#include <math/seadVector.h>

namespace al {
class LiveActor;
class ActorInitInfo;
class CollisionPartsFilterBase;
class HitSensor;
class AreaObj;
}  // namespace al

class HackCap;
class IUseDimension;

class PlayerRecoverySafetyPoint {
private:
    // missing member fields

public:
    PlayerRecoverySafetyPoint(const al::LiveActor*, const HackCap*, const al::ActorInitInfo&, const IUseDimension*, al::CollisionPartsFilterBase*,
                              al::HitSensor*);
    void checkInvalidateArea();
    void endRecovery();
    // unknown return types
    void* getSafetyPoint() const;
    void* getSafetyPointArea() const;
    void* getSafetyPointGravity() const;

    bool isActiveRecoveryArea() const;
    bool isEnableRecovery() const;
    bool isValid() const;
    void noticeDangerousPoint(const sead::Vector3f&, bool);
    void noticeRequestSafetyPoint(const sead::Vector3f&, const sead::Vector3f&, const al::AreaObj*);
    void reset();
    void setRecoveryArea(const al::AreaObj*);
    void setSafetyPoint(const sead::Vector3f&, const sead::Vector3f&, const al::AreaObj*);
    void slideLastSafetyPoint(sead::Vector3f*, sead::Vector3f*, bool, const sead::Vector3f&, bool, al::CollisionPartsFilterBase*);
    void startBubbleWait();
    void startRecovery(f32);
    void updateRecoveryAreaValidity();
    void updateRecoveryBubble();
};