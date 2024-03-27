#include "Player/PlayerTrigger.h"

PlayerTrigger::PlayerTrigger() {}

/*
 * PlayerTrigger::clear
 */

void PlayerTrigger::clearCollisionTrigger() {
    mCollisionFlags.makeAllZero();
}

void PlayerTrigger::clearAttackSensorTrigger() {
    mAttackSensorFlags.makeAllZero();
}

void PlayerTrigger::clearActionTrigger() {
    mActionFlags.makeAllZero();
}

void PlayerTrigger::clearReceiveSensorTrigger() {
    mReceiveSensorFlags.makeAllZero();
    mRecMaterialCode = nullptr;
}

void PlayerTrigger::clearPreMovementTrigger() {
    mPreMovementFlags.makeAllZero();
}

void PlayerTrigger::clearDemoEndTrigger() {
    mDemoEndFlags.makeAllZero();
}

void PlayerTrigger::clearMaterialChangeTrigger() {
    mMaterialChangeFlags.makeAllZero();
}

/*
 * PlayerTrigger::isOn
 */

bool PlayerTrigger::isOn(PlayerTrigger::ECollisionTrigger trigger) const {
    return mCollisionFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EAttackSensorTrigger trigger) const {
    return mAttackSensorFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EActionTrigger trigger) const {
    return mActionFlags.isOnBit((s64)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EReceiveSensorTrigger trigger) const {
    return mReceiveSensorFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EPreMovementTrigger trigger) const {
    return mPreMovementFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EDemoEndTrigger trigger) const {
    return mDemoEndFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOn(PlayerTrigger::EMaterialChangeTrigger trigger) const {
    return mMaterialChangeFlags.isOnBit((s32)trigger);
}

bool PlayerTrigger::isOnAnyDamage() const {
    if (isOn(PlayerTrigger::ECollisionTrigger::field_2) || isOn(PlayerTrigger::ECollisionTrigger::field_6))
        return true;

    if (isOn(PlayerTrigger::EReceiveSensorTrigger::field_0))
        return true;

    if (isOn(PlayerTrigger::EActionTrigger::field_17))
        return true;

    if (isOnDamageFire())
        return true;

    if (isOnEndHackWithDamage())
        return true;

    return false;
}

bool PlayerTrigger::isOnCollisionExpandCheck() const {
    return mActionFlags.isOnBit((u64)PlayerTrigger::EActionTrigger::cCollisionExpandCheck);
}

bool PlayerTrigger::isOnDamageFire() const {
    return isOn(PlayerTrigger::ECollisionTrigger::field_3) || isOn(PlayerTrigger::ECollisionTrigger::field_4) ||
           isOn(PlayerTrigger::EReceiveSensorTrigger::field_1);
}

bool PlayerTrigger::isOnEndHackWithDamage() const {
    return isOn(PlayerTrigger::EReceiveSensorTrigger::field_2) || isOn(PlayerTrigger::EReceiveSensorTrigger::field_3);
}

bool PlayerTrigger::isOnHipDropCancelThrow() const {
    return isOn(PlayerTrigger::EActionTrigger::cHipDropCancelThrow);
}

bool PlayerTrigger::isOnNoDamageDown() const {
    if (!isOn(PlayerTrigger::EActionTrigger::field_a))
        return isOn(PlayerTrigger::EPreMovementTrigger::field_4);
    return true;
}

bool PlayerTrigger::isOnSpinMoveCapThrow() const {
    return isOn(PlayerTrigger::EActionTrigger::field_1b) || isOn(PlayerTrigger::EActionTrigger::field_1c);
}

bool PlayerTrigger::isOnUpperPunchHit() const {
    if (!isOn(PlayerTrigger::ECollisionTrigger::field_0))
        return isOn(PlayerTrigger::EAttackSensorTrigger::cUpperPunchHitToss);
    return true;
}

bool PlayerTrigger::isOnUpperPunchHitToss() const {
    return isOn(PlayerTrigger::EAttackSensorTrigger::cUpperPunchHitToss);
}

bool PlayerTrigger::isOnYoshiHackEnd() const {
    return isOn(PlayerTrigger::ECollisionTrigger::cYoshiHackEnd);
}

/*
 * PlayerTrigger::set
 */

void PlayerTrigger::set(PlayerTrigger::ECollisionTrigger trigger) {
    mCollisionFlags.setBit((s32)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EAttackSensorTrigger trigger) {
    mAttackSensorFlags.setBit((s32)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EActionTrigger trigger) {
    mActionFlags.setBit((s64)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EReceiveSensorTrigger trigger) {
    mReceiveSensorFlags.setBit((s32)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EPreMovementTrigger trigger) {
    mPreMovementFlags.setBit((s32)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EDemoEndTrigger trigger) {
    mDemoEndFlags.setBit((s32)trigger);
}

void PlayerTrigger::set(PlayerTrigger::EMaterialChangeTrigger trigger) {
    mMaterialChangeFlags.setBit((s32)trigger);
}

void PlayerTrigger::setRecMaterialTrigger(const char* materialCode) {
    mRecMaterialCode = materialCode;
}

bool PlayerTrigger::tryGetRecMaterialCode(const char** materialCode) const {
    if (mRecMaterialCode) {
        *materialCode = mRecMaterialCode;
        return true;
    }

    return false;
}
