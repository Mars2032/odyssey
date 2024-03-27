#pragma once

namespace al {
class LiveActor;
}  // namespace al

namespace alCameraBlurFunction {
void resetCameraBlurName(const al::LiveActor*);
void setCameraBlurName(const al::LiveActor*, const char* name);
}  // namespace alCameraBlurFunction