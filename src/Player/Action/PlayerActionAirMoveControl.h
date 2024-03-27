#pragma once

namespace al {
class LiveActor;
}

class PlayerConst;
class PlayerInput;
class IUsePlayerCollision;

class PlayerActionAirMoveControl {
public:
    PlayerActionAirMoveControl(al::LiveActor* parent, const PlayerConst* playerConst, const PlayerInput* playerInput,
                               const IUsePlayerCollision* playerCollision, bool);

    void setup(f32, f32, s32, f32, f32, s32, f32);
    void setupTurn(f32, f32, f32, f32, s32, s32, s32);
    void setExtendFrame(s32);
    void setupCollideWallScaleVelocity(f32, f32, f32);
    void verticalizeStartMoveDir(const sead::Vector3f&);
    void update();
    bool isHoldJumpExtend() const;
    void calcMoveInput(sead::Vector3f*, const sead::Vector3f&) const;
};