#pragma once

#include <al/Library/Nerve/NerveExecutor.h>

class EventFlowSceneExecuteCtrl;

namespace al {
class PlayerHolder;
class CameraDirector;
class CollisionDirector;
class MessageSystem;
class ActorInitInfo;
}  // namespace al

class NpcEventDirector : public al::NerveExecutor {
public:
    NpcEventDirector(const al::PlayerHolder*, al::CameraDirector*, al::CollisionDirector*, const al::MessageSystem*, EventFlowSceneExecuteCtrl*);
    void init(const al::ActorInitInfo&);
    void execute();
    void updateBalloon();
    void killAllBalloonForSnapShotMode();
    void exeWait();
    void exeDemo();
    void exeDemoWipeClose();
    void exeDemoWipeOpen();
    void exeDemoTalk();
    void endDemoTalk();
    void exeDemoTalkEnd();
    void exeDemoSelectChoiceStart();
    void exeDemoSelectChoice();
    ~NpcEventDirector();
    void getCameraDirector() const;
    void getCollisionDirector() const;
    void getSceneObjHolder() const;
    void getMessageSystem() const;
};