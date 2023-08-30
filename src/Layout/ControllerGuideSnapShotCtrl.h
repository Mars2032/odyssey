#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

namespace al {
class LayoutInitInfo;
class PostProcessingFilter;
class SimpleLayoutAppearWaitEnd;
class ParameterIo;
class ParameterArray;
class ViewDepthDrawParam;
}  // namespace al

class ControllerGuideSnapShotCtrl : public al::NerveStateBase {
private:
    al::SimpleLayoutAppearWaitEnd* mControllerGuideSnapShot;
    al::SimpleLayoutAppearWaitEnd* mControllerGuideSnapShotFrame;
    al::SimpleLayoutAppearWaitEnd* mControllerGuideSnapShotLogo;
    al::PostProcessingFilter* mPostProcessingFilter;
    al::ParameterIo* mParameterIo;
    al::ParameterArray* mParameterArray;
    al::ViewDepthDrawParam* mViewDepthDrawParam;  // class unsure
    s32 field_50;
    s32 field_54;
    s32 field_58;
    bool field_5c;
    s32 field_60;

public:
    ControllerGuideSnapShotCtrl(const char*, const al::LayoutInitInfo&, al::PostProcessingFilter*);
    ~ControllerGuideSnapShotCtrl() override;
    void control() override;
    void appearLogo(s32);
    void start();
    void end();
    void setFilterName(s32);
    void exeHide();
    void exeShow();
    void exeEnd();
    void exeEndByButton();
    void exeHideByButton();
    void exeShowByButton();
    void appearLogo(s32, bool);

    al::SimpleLayoutAppearWaitEnd* getSnapShotFrameLayout() const { return mControllerGuideSnapShotFrame; }
};