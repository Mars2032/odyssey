#pragma once

#include <basis/seadTypes.h>

namespace al {
class LiveActor;
}

namespace rs {
bool isPlayerDamageStopDemo(const al::LiveActor*);
bool isPlayerHackType(const al::LiveActor*, s32);
bool isPlayerHackRigidBody(const al::LiveActor*);
bool isPlayerHackJugemFishing(const al::LiveActor*);
bool isPlayerHackKuriboAny(const al::LiveActor*);
bool isPlayerHackKuribo(const al::LiveActor*);
bool isPlayerHackKuriboWing(const al::LiveActor*);
bool isPlayerHackStatueMario(const al::LiveActor*);
bool isPlayerHackEnemy(const al::LiveActor*);
bool isPlayerHackTrilemmaRock(const al::LiveActor*);
bool isPlayerHackTrilemmaPaper(const al::LiveActor*);
bool isPlayerHackTrilemmaScissors(const al::LiveActor*);
bool isPlayerHackElectricWire(const al::LiveActor*);
bool isPlayerHackTRex(const al::LiveActor*);
bool isPlayerHackFukankun(const al::LiveActor*);
bool isPlayerHackHosui(const al::LiveActor*);
bool isPlayerHackYoshi(const al::LiveActor*);
bool isPlayerHackYukimaru(const al::LiveActor*);
bool isPlayerHackHammerBros(const al::LiveActor*);
bool isPlayerHackBazookaElectric(const al::LiveActor*);
bool isPlayerHackBubble(const al::LiveActor*);
bool isPlayerHackTank(const al::LiveActor*);
bool isPlayerHackTsukkun(const al::LiveActor*);
bool isPlayerHackPukupuku(const al::LiveActor*);
bool isPlayerHackPukupukuAll(const al::LiveActor*);
bool isPlayerHackRadiconNpc(const al::LiveActor*);
bool isPlayerHackSenobi(const al::LiveActor*);
bool isPlayerHackKakku(const al::LiveActor*);
bool isPlayerHackGroupTalkScare(const al::LiveActor*);
bool isPlayerHackGroupUseCameraStick(const al::LiveActor*);
bool isPlayerHackNoSeparateCameraInput(const al::LiveActor*);
bool isPlayerEnableToSeeOddSpace(const al::LiveActor*);
bool isPlayerMini(const al::LiveActor*);
bool isPlayer3D(const al::LiveActor*);
bool isPlayer2D(const al::LiveActor*);
bool isPlayerSquat(const al::LiveActor*);
bool isPlayerInWater(const al::LiveActor*);
bool isPlayerPoleClimb(const al::LiveActor*);
bool isPlayerWallCatch(const al::LiveActor*);
}  // namespace rs
