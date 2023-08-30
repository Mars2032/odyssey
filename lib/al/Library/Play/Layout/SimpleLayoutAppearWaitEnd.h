#pragma once

#include <al/Library/Layout/LayoutActor.h>

namespace al {
class LayoutInitInfo;

class SimpleLayoutAppearWaitEnd : public al::LayoutActor {
public:
    SimpleLayoutAppearWaitEnd(const char*, const char*, const al::LayoutInitInfo&, const char*, bool);
    SimpleLayoutAppearWaitEnd(al::LayoutActor*, const char*, const char*, const al::LayoutInitInfo&, const char*);
    void appear();
    void end();
    void startWait();
    void exeAppear();
    void exeWait();
    void exeEnd();
    bool isWait() const;
    bool isAppearOrWait() const;
};
}  // namespace al
