#pragma once

namespace al {
class LiveActor;
}

class IUsePlayerCollision;

namespace rs {
void waitGround(al::LiveActor* actor, const IUsePlayerCollision* collision, f32, f32, f32, f32);
void calcGroundNormalOrUpDir(sead::Vector3f* out, const al::LiveActor* actor, const IUsePlayerCollision* playerCollision);
}  // namespace rs