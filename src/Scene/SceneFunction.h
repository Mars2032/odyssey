#pragma once

class ProjectItemDirector;

namespace al {
class IUseSceneObjHolder;
class Scene;
}  // namespace al

namespace rs {
void endDemoCommonProc(al::Scene*, ProjectItemDirector*);
void updateKitListPostSnapShot(al::Scene*);
}  // namespace rs

namespace ScenePlayerFunction {
void startSnapShotMode(const al::Scene*);
void endSnapShotMode(const al::Scene*);
void updatePlayerDither(const al::Scene*);
}  // namespace ScenePlayerFunction

namespace SceneEventNotifyFunction {
void notifySnapShotModeOn(const al::IUseSceneObjHolder*);
void notifySnapShotModeOff(const al::IUseSceneObjHolder*);
}  // namespace SceneEventNotifyFunction