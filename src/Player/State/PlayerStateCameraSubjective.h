#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

namespace al {
class CameraTicket;

}  // namespace al

class PlayerConst;
class IUsePlayerCollision;
class PlayerInput;
class IPlayerModelChanger;
class PlayerCarryKeeper;
class PlayerAnimator;

class PlayerStateCameraSubjective : public al::ActorStateBase {
private:
    const PlayerConst* mPlayerConst;
    const IUsePlayerCollision* mPlayerCollider;
    const PlayerInput* mPlayerInput;
    s32 mConvergeRate = 0.0f;
    bool mIsInterruptByDemo = false;
    al::CameraTicket* mCameraSubjective;
    IPlayerModelChanger* mPlayerModelChanger;
    PlayerCarryKeeper* mPlayerCarryKeeper;
    PlayerAnimator* mPlayerAnimator;

public:
    PlayerStateCameraSubjective(al::LiveActor* parent, al::CameraTicket* camera, IPlayerModelChanger* modelChanger, PlayerCarryKeeper* carryKeeper,
                                PlayerAnimator* playerAnimator, const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                                const PlayerInput* playerInput);
    ~PlayerStateCameraSubjective();
    void appear();
    inline void end();
    void kill();
    void control();
    void interruptByDemo();
    bool isStateActiveCamera() const;
    void exeStart();
    void faceToCameraDir();
    void exeWait();
    void exeEnd();
};
