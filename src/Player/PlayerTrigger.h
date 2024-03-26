#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

class PlayerTrigger {
public:
    enum class ECollisionTrigger;
    enum class EAttackSensorTrigger;
    enum class EActionTrigger;
    enum class EReceiveSensorTrigger;
    enum class EPreMovementTrigger;
    enum class EDemoEndTrigger;
    enum class EMaterialChangeTrigger;

private:
    sead::BitFlag32 mCollisionFlags = 0;
    sead::BitFlag32 mAttackSensorFlags = 0;
    sead::BitFlag64 mActionFlags = 0;
    sead::BitFlag32 mReceiveSensorFlags = 0;
    sead::BitFlag32 mPreMovementFlags = 0;
    sead::BitFlag32 mDemoEndFlags = 0;
    sead::BitFlag32 mMaterialChangeFlags = 0;
    const char* mRecMaterialCode = nullptr;

public:
    PlayerTrigger();

    void clearCollisionTrigger();
    void clearAttackSensorTrigger();
    void clearActionTrigger();
    void clearReceiveSensorTrigger();
    void clearPreMovementTrigger();
    void clearDemoEndTrigger();
    void clearMaterialChangeTrigger();

    bool isOn(PlayerTrigger::ECollisionTrigger trigger) const;
    bool isOn(PlayerTrigger::EAttackSensorTrigger trigger) const;
    bool isOn(PlayerTrigger::EActionTrigger trigger) const;
    bool isOn(PlayerTrigger::EReceiveSensorTrigger trigger) const;
    bool isOn(PlayerTrigger::EPreMovementTrigger trigger) const;
    bool isOn(PlayerTrigger::EDemoEndTrigger trigger) const;
    bool isOn(PlayerTrigger::EMaterialChangeTrigger trigger) const;

    void set(PlayerTrigger::ECollisionTrigger trigger);
    void set(PlayerTrigger::EAttackSensorTrigger trigger);
    void set(PlayerTrigger::EActionTrigger trigger);
    void set(PlayerTrigger::EReceiveSensorTrigger trigger);
    void set(PlayerTrigger::EPreMovementTrigger trigger);
    void set(PlayerTrigger::EDemoEndTrigger trigger);
    void set(PlayerTrigger::EMaterialChangeTrigger trigger);

    bool isOnAnyDamage() const;
    bool isOnCollisionExpandCheck() const;
    bool isOnDamageFire() const;
    bool isOnEndHackWithDamage() const;
    bool isOnHipDropCancelThrow() const;
    bool isOnNoDamageDown() const;
    bool isOnSpinMoveCapThrow() const;
    bool isOnUpperPunchHit() const;
    bool isOnUpperPunchHitToss() const;
    bool isOnYoshiHackEnd() const;

    void setRecMaterialTrigger(const char* materialCode);
    bool tryGetRecMaterialCode(const char** materialCode) const;
};

enum class PlayerTrigger::ECollisionTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    cYoshiHackEnd,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};

enum class PlayerTrigger::EAttackSensorTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    cUpperPunchHitToss,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};

enum class PlayerTrigger::EActionTrigger {
    field_0,
    field_1,
    field_2,
    cCollisionExpandCheck,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    cHipDropCancelThrow,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f,
    field_20,
    field_21,
    field_22,
    field_23,
    field_24,
    field_25,
    field_26,
    field_27,
    field_28,
    field_29,
    field_2a,
    field_2b,
    field_2c,
    field_2d,
    field_2e,
    field_2f,
    field_30,
    field_31,
    field_32,
    field_33,
    field_34,
    field_35,
    field_36,
    field_37,
    field_38,
    field_39,
    field_3a,
    field_3b,
    field_3c,
    field_3d,
    field_3e,
    field_3f
};

enum class PlayerTrigger::EReceiveSensorTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};

enum class PlayerTrigger::EPreMovementTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};

enum class PlayerTrigger::EDemoEndTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};

enum class PlayerTrigger::EMaterialChangeTrigger {
    field_0,
    field_1,
    field_2,
    field_3,
    field_4,
    field_5,
    field_6,
    field_7,
    field_8,
    field_9,
    field_a,
    field_b,
    field_c,
    field_d,
    field_e,
    field_f,
    field_10,
    field_11,
    field_12,
    field_13,
    field_14,
    field_15,
    field_16,
    field_17,
    field_18,
    field_19,
    field_1a,
    field_1b,
    field_1c,
    field_1d,
    field_1e,
    field_1f
};