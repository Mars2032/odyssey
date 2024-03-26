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
};