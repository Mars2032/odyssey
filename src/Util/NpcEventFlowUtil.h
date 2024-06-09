#pragma once

namespace al {
class LiveActor;
}

class IUsePlayerCollision;

namespace rs {
void waitGround(al::LiveActor* actor, const IUsePlayerCollision* collision, f32, f32, f32, f32);
void calcGroundNormalOrUpDir(sead::Vector3f* out, const al::LiveActor* actor, const IUsePlayerCollision* playerCollision);
void slerpUp(al::LiveActor*, const sead::Vector3f&, f32, f32);
void faceToCamera(al::LiveActor*);
}  // namespace rs