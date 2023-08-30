#pragma once

namespace al {
class Scene;
class PlayerHolder;

void updateKit(al::Scene*);
void updateGraphicsPrev(al::Scene*);
void updateKitList(al::Scene*, const char*);
void updateKitListPostOnNerveEnd(al::Scene*);
void updateKitListPrev(al::Scene*);
void updateKitListPostDemoWithPauseNormalEffect(al::Scene*);
void updateKitTable(al::Scene*, const char*);
void pausePadRumble(const al::Scene*);
void endPausePadRumble(const al::Scene*);
al::PlayerHolder* getScenePlayerHolder(const al::Scene*);
void startCameraSnapShotMode(al::Scene*, bool);
void endCameraSnapShotMode(al::Scene*);
void validatePostProcessingFilter(const al::Scene*);
void invalidatePostProcessingFilter(const al::Scene*);
void incrementPostProcessingFilterPreset(const al::Scene*);
void decrementPostProcessingFilterPreset(const al::Scene*);
s32 getPostProcessingFilterPresetId(const al::Scene*);
}  // namespace al