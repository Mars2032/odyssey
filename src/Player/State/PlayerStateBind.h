#pragma once

#include <al/Library/Nerve/NerveStateBase.h>

class PlayerConst;
class PlayerPuppet;
class PlayerTrigger;
class PlayerActionAirMoveControl;
class PlayerInput;
class IUsePlayerCollision;

class PlayerStateBind : public al::ActorStateBase {
private:
    const PlayerConst* mPlayerConst;
    const PlayerPuppet* mPlayerPuppet;
    PlayerTrigger* mPlayerTrigger;
    PlayerActionAirMoveControl* mPlayerActionAirMoveCtrl = nullptr;

public:
    PlayerStateBind(al::LiveActor* parent, const PlayerConst* playerConst, const PlayerInput* playerInput, const PlayerPuppet* playerPuppet,
                    const IUsePlayerCollision* playerCollision, PlayerTrigger* playerTrigger);
    ~PlayerStateBind();
    void appear() override;
    void endBind();
    void exeBind();
    void exeEndCapThrow();
    void exeEndFall();
    void exeEndJump();
    void exeEndOnGround();
    bool isEndAir() const;
    bool isEndCapThrow() const;
    bool isEndOnGround() const;
    bool isInvalidInput() const;
};
