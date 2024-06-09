#pragma once

class IUsePlayerCollision;

namespace rs {
bool isJustLand(const IUsePlayerCollision*);
bool isOnGround(const al::LiveActor*, const IUsePlayerCollision*);

bool isCollisionCodeDamageFireGround(const IUsePlayerCollision*);
bool isCollisionCodeDamageFireWall(const IUsePlayerCollision*);
bool isCollisionCodeDamageFireCeiling(const IUsePlayerCollision*);

}  // namespace rs