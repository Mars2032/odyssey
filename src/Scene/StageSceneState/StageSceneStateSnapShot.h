#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

class ControllerGuideSnapShotCtrl;
class SceneAudioSystemPauseController;
class InputSeparator;
class NpcEventDirector;

namespace al {
class Scene;
}

class StageSceneStateSnapShot : public al::NerveStateBase {
private:
    al::Scene* mParent;
    ControllerGuideSnapShotCtrl* mControllerGuideSnapShotCtrl;
    SceneAudioSystemPauseController* mAudioPauseController;
    InputSeparator* mInputSeparator;
    NpcEventDirector* mNpcEventDirector;

public:
    StageSceneStateSnapShot(const char* stateName, al::Scene* parent, ControllerGuideSnapShotCtrl* snapShotCtrl,
                            SceneAudioSystemPauseController* audioController, InputSeparator* inputSeparator, NpcEventDirector* npcEventDirector);
    ~StageSceneStateSnapShot() override{};
    void appear() override;
    void kill() override;
    void exeWait();
    bool tryStart();
};
