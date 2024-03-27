#pragma once

#include <math/seadVector.h>

namespace al {
class IUseCamera;
class CameraTicket;

void calcCameraFront(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
void calcCameraUpDir(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
void calcCameraLookDir(sead::Vector3f* out, const al::IUseCamera* cameraUser, s32);
void setCameraInterpoleStep(al::CameraTicket* ticket, s32 step);
bool isActiveCameraInterpole(const al::IUseCamera*, s32);
void endCamera(const al::IUseCamera*, al::CameraTicket*, s32, bool);
void startCamera(const al::IUseCamera*, al::CameraTicket*, s32);

bool isActiveCamera(const al::CameraTicket*);
}  // namespace al