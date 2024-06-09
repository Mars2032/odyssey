#pragma once

#include <math/seadVector.h>

class IUsePlayerCollision;

namespace rs {
const sead::Vector3f& getCollidedGroundNormal(const IUsePlayerCollision*);
const sead::Vector3f& getCollidedWallNormal(const IUsePlayerCollision*);
const sead::Vector3f& getCollidedCeilingNormal(const IUsePlayerCollision*);
void calcGroundNormalOrGravityDir(sead::Vector3f* out, const al::LiveActor* actor, const IUsePlayerCollision*);
}  // namespace rs