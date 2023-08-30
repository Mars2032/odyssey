#pragma once

#include <al/Project/Execute/ExecuteSystemInitInfo.h>
#include <basis/seadTypes.h>

namespace al {
class GraphicsInitArg;
class LiveActorGroup;
class CameraDirector;
class ClippingDirector;
class CollisionDirector;
class PlayerHolder;
class HitSensorDirector;
class ScreenPointDirector;
class ShadowDirector;
class StageSwitchDirector;
class SwitchAreaDirector;
class LiveActorGroup;
class GamePadSystem;
class PadRumbleDirector;
class NatureDirector;
class ModelGroup;
class ActorResourceHolder;
class AreaObjDirector;
class ExecuteDirector;
class GravityHolder;
class EffectSystem;
class GraphicsSystemInfo;
class ModelDrawBufferUpdater;
class ExecuteAsyncExectuor;
class ModelDisplayListController;

class LiveActorKit {
private:
    s32 mActorMaxCount;
    al::ActorResourceHolder* mActorResourceHolder;
    al::AreaObjDirector* mAreaObjDirector;
    al::ExecuteDirector* mExecuteDirector;
    al::GravityHolder* mGravityHolder;
    al::EffectSystem* mEffectSystem;
    al::GraphicsSystemInfo* mGraphicsSystemInfo;
    void* field_40;
    al::ModelDrawBufferUpdater* mModelDrawBufferUpdater;
    al::ExecuteAsyncExectuor* mExecuteAsyncExecutorCore1;
    al::ExecuteAsyncExectuor* mExecuteAsyncExecutorCore2;
    al::ModelDisplayListController* mModelDisplayListController;
    al::ExecuteSystemInitInfo mExecuteSystemInfo;
    al::LiveActorGroup* mActorDrawingGroup;
    al::CameraDirector* mCameraDirector;
    al::ClippingDirector* mClippingDirector;
    al::CollisionDirector* mCollisionDirector;
    void* field_90;
    al::PlayerHolder* mPlayerHolder;
    al::HitSensorDirector* mHitSensorDirector;
    al::ScreenPointDirector* screenPointDirector;
    al::ShadowDirector* mShadowDirector;
    al::StageSwitchDirector* mStageSwitchDirector;
    al::SwitchAreaDirector* mSwitchAreaDirector;
    al::LiveActorGroup* mAllActorsGroup;
    void* field_d0;
    al::GamePadSystem* mGamePadSystem;
    al::PadRumbleDirector* mPadRumbleDirector;
    al::NatureDirector* mNatureDirector;
    al::ModelGroup* mModelGroup;

public:
    LiveActorKit(s32, s32);
    virtual ~LiveActorKit();
    void init(s32);
    void initGraphics(const al::GraphicsInitArg&);
    void initHitSensorDirector();
    void initGravityHolder();
    void initShadowDirector();
    void initEffectSystem();
    void initSwitchAreaDirector(s32, s32);
    void initNatureDirector();
    void endInit();
    void update(const char*);
    void clearGraphicsRequest();
    void updateGraphics();
    void preDrawGraphics();

    al::EffectSystem* getEffectSystem() const { return mEffectSystem; }
};
}  // namespace al