#pragma once

#include <framework/seadGameFrameworkNx.h>

namespace agl {
class DrawContext;
class RenderBuffer;
class RenderTargetColor;
}  // namespace agl

namespace al {
class GameFrameworkNx : public sead::GameFrameworkNx {
    SEAD_RTTI_OVERRIDE(al::GameFrameworkNx, sead::GameFrameworkNx);
    // missing member vars
public:
    GameFrameworkNx(const sead::GameFrameworkNx::CreateArg&);
    void createControllerMgr(sead::TaskBase*);
    void initAgl(sead::Heap*, s32, s32, s32, s32, s32, s32);
    void createInfLoopChecker(sead::TaskBase*, const sead::TickSpan&, s32);
    void clearFrameBuffer();
    void procFrame_();
    void procDraw_();
    void present_();
};
}  // namespace al