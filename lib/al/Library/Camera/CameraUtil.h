#pragma once

#include <math/seadVectorFwd.h>

namespace al {
class IUseCamera;

void calcCameraFront(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
void calcCameraUpDir(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
void calcCameraLookDir(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
}  // namespace al