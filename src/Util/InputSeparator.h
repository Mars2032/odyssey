#pragma once

#include <basis/seadTypes.h>

namespace al {
class IUseSceneObjHolder;
}

class InputSeparator {
private:
    const al::IUseSceneObjHolder* mSceneObjHolder;
    bool field_8;
    bool field_9;
    s32 field_c; // initialzed to 8, never changed.
    s32 field_10; // seems like a bitmask?

public:
    InputSeparator(const al::IUseSceneObjHolder*, bool);
    void reset();
    void update();
    void updateForSnapShotMode();
    bool isTriggerUiLeft();
    void checkDominant(bool);
    bool isTriggerUiRight();
    bool isTriggerUiUp();
    bool isTriggerUiDown();
    bool isHoldUiLeft();
    bool isHoldUiRight();
    bool isHoldUiUp();
    bool isHoldUiDown();
    bool isRepeatUiLeft();
    bool isRepeatUiRight();
    bool isRepeatUiUp();
    bool isRepeatUiDown();
    bool isTriggerSnapShotMode();
    bool isTriggerIncrementPostProcessingFilterPreset();
    bool isTriggerDecrementPostProcessingFilterPreset();
};