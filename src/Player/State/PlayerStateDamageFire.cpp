#include "Player/State/PlayerStateDamageFire.h"

#include <Player/PlayerFunction.h>
#include <Util/ColliderDisk.h>
#include <Util/NpcEventFlowUtil.h>
#include <Util/PlayerCollisionUtil.h>
#include <Util/StageSceneFunction.h>
#include <al/Library/LiveActor/ActorActionFunction.h>
#include <al/Library/LiveActor/ActorMovementFunction.h>
#include <al/Library/LiveActor/ActorPoseKeeper.h>
#include <al/Library/Math/MathUtil.h>
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/Nerve/NerveUtil.h>

#include "Player/Action/PlayerActionAirMoveControl.h"
#include "Player/Action/PlayerActionGroundMoveControl.h"
#include "Player/PlayerAnimator.h"
#include "Player/PlayerConst.h"
#include "Player/PlayerInput.h"

namespace {
NERVE_IMPL(PlayerStateDamageFire, Jump);
NERVE_IMPL(PlayerStateDamageFire, Dead);
NERVE_IMPL(PlayerStateDamageFire, Run);
NERVE_IMPL(PlayerStateDamageFire, Fall);
NERVE_IMPL(PlayerStateDamageFire, Jump2nd);
NERVE_MAKE(PlayerStateDamageFire, Jump2nd);
struct {
    NERVE_MAKE(PlayerStateDamageFire, Jump);
    NERVE_MAKE(PlayerStateDamageFire, Dead);
    NERVE_MAKE(PlayerStateDamageFire, Run);
    NERVE_MAKE(PlayerStateDamageFire, Fall);

} nrvPlayerStateDamageFire;
}  // namespace

PlayerStateDamageFire::PlayerStateDamageFire(al::LiveActor* parent, const PlayerConst* playerConst, const IUsePlayerCollision* playerCollision,
                                             const PlayerInput* playerInput, PlayerAnimator* playerAnimator, IJudge* playerJudgeSpeedCheckFall)
    : ActorStateBase("ダメージ", parent), mPlayerConst(playerConst), mPlayerCollider(playerCollision), mPlayerInput(playerInput),
      mPlayerAnimator(playerAnimator), mPlayerJudgeSpeedCheckFall(playerJudgeSpeedCheckFall) {
    mPlayerActionAirMoveCtrl = new PlayerActionAirMoveControl(parent, playerConst, playerInput, playerCollision, false);
    mPlayerActionGroundMoveCtrl = new PlayerActionGroundMoveControl(parent, mPlayerConst, mPlayerInput, mPlayerCollider);

    mPlayerActionGroundMoveCtrl->set_field_bb(true);
    mPlayerActionGroundMoveCtrl->set_field_b8(true);
    mPlayerActionGroundMoveCtrl->set_field_b9(true);

    initNerve(&nrvPlayerStateDamageFire.Jump, 0);
}

PlayerStateDamageFire::~PlayerStateDamageFire() = default;

void PlayerStateDamageFire::appear() {
    setDead(false);
    mPlayerActionGroundMoveCtrl->setup(mPlayerConst->getDamageFireRunSpeed(), mPlayerConst->getDamageFireRunSpeed(), 1, 9999, 9999,
                                       mPlayerConst->getGravityMove(), 10000.0f, 10000);
    mDamageFireTimer = 0;
    if (PlayerFunction::isPlayerDeadStatus(getParent())) {
        al::setVelocityZero(getParent());
        al::setNerve(this, &nrvPlayerStateDamageFire.Dead);
        return;
    }

    if (rs::isJustLand(mPlayerCollider)) {
        sead::Vector3f alongNormalH = {0.0f, 0.0f, 0.0f};
        al::alongVectorNormalH(&alongNormalH, al::getVelocity(getParent()), -al::getGravity(getParent()),
                               rs::getCollidedGroundNormal(mPlayerCollider));

        al::setVelocity(getParent(), alongNormalH - rs::getCollidedGroundNormal(mPlayerCollider) * mPlayerConst->getGravity());
    }
    mIsDamageFireGround = rs::isCollisionCodeDamageFireGround(mPlayerCollider);
    mIsDamageFireWall = rs::isCollisionCodeDamageFireWall(mPlayerCollider);
    mIsDamageFireCeiling = rs::isCollisionCodeDamageFireCeiling(mPlayerCollider);
    al::setNerve(this, &nrvPlayerStateDamageFire.Jump);
}

void PlayerStateDamageFire::control() {
    if (al::isNerve(this, &nrvPlayerStateDamageFire.Run) || al::isNerve(this, &nrvPlayerStateDamageFire.Fall)) {
        if (mDamageFireTimer >= mPlayerConst->getDamageFireRunTime())
            kill();
        mDamageFireTimer++;
    }
}

bool PlayerStateDamageFire::isEndFirstLand() const {
    return !al::isNerve(this, &nrvPlayerStateDamageFire.Jump);
}

bool PlayerStateDamageFire::isEnableJump() const {
    return al::isNerve(this, &nrvPlayerStateDamageFire.Run);
}

bool PlayerStateDamageFire::isEnablePeachAmiibo() const {
    if (isDead())
        return true;

    return !al::isNerve(this, &nrvPlayerStateDamageFire.Jump);
}

s32 PlayerStateDamageFire::getEnableCancelCollisionSnapFrame() const {
    return 20;
}

void PlayerStateDamageFire::exeJump() {
    if (al::isFirstStep(this)) {
        mPlayerAnimator->startAnim("FireRunStart");
        al::startHitReaction(getParent(), "あちちジャンプ");
        if ((!mIsDamageFireWall || mIsDamageFireGround)) {
            if (!mIsDamageFireCeiling) {
                sead::Vector3f groundNormal = {0.0f, 0.0f, 0.0f};
                rs::calcGroundNormalOrGravityDir(&groundNormal, getParent(), mPlayerCollider);
                sead::Vector3f vertical = {0.0f, 0.0f, 0.0f};
                sead::Vector3f parallel = {0.0f, 0.0f, 0.0f};
                al::separateVectorParallelVertical(&parallel, &vertical, groundNormal, al::getVelocity(getParent()));
                f32 moveSpeed = mIsDamageFireWall ? mPlayerConst->getDamageFireJumpMoveSpeed() : vertical.length();
                sead::Vector3f moveDir = {0.0f, 0.0f, 0.0f};
                if (!mIsDamageFireWall) {
                    mPlayerInput->calcMoveDirection(&moveDir, groundNormal);
                } else {
                    moveDir = rs::getCollidedWallNormal(mPlayerCollider);
                }
                bool isNearZero = al::isNearZero(moveDir, 0.001f);
                auto parent = getParent();
                sead::Vector3f result = {};
                sead::Vector3f* velocity = &result;
                if (!isNearZero) {
                    result = moveSpeed * moveDir;
                    result += parallel;
                } else {
                    velocity = &parallel;
                }
                al::setVelocity(parent, *velocity);

                mPlayerActionAirMoveCtrl->setup(mPlayerConst->getDamageFireJumpMoveSpeed(), mPlayerConst->getDamageFireJumpMoveSpeed(),
                                                mPlayerConst->getDamageFireNoGravityFrame(), mPlayerConst->getDamageFireJumpPower1st(),
                                                mPlayerConst->getDamageFireGravity(), mIsDamageFireWall ? 10 : 0, mPlayerConst->getJumpInertiaRate());

                ((u8*)mPlayerActionAirMoveCtrl)[0x32] = true;
            } else {
                goto ceiling;  // what the fuck nintendo? is this real??
            }

        } else if (!mIsDamageFireCeiling) {
            sead::Vector3f wallNormal = rs::getCollidedWallNormal(mPlayerCollider);
            auto parent = getParent();
            sead::Vector3f velocity = wallNormal * mPlayerConst->getDamageFireJumpMoveSpeed();
            al::setVelocity(parent, velocity);
            mPlayerActionAirMoveCtrl->setup(mPlayerConst->getDamageFireJumpMoveSpeed(), mPlayerConst->getDamageFireJumpMoveSpeed(), 0,
                                            mPlayerConst->getDamageFireJumpPower2nd(), mPlayerConst->getDamageFireGravity(), 10,
                                            mPlayerConst->getJumpInertiaRate());

            al::faceToDirection(getParent(), wallNormal);

        } else {
        ceiling:
            sead::Vector3f ceilingNormal = rs::getCollidedCeilingNormal(mPlayerCollider);
            sead::Vector3f vertical = {0.0f, 0.0f, 0.0f};
            sead::Vector3f parallel = {0.0f, 0.0f, 0.0f};
            al::separateVectorParallelVertical(&parallel, &vertical, ceilingNormal, al::getVelocity(getParent()));
            f32 moveSpeed = mIsDamageFireWall ? mPlayerConst->getDamageFireJumpMoveSpeed() : vertical.length();
            parallel = mPlayerConst->getDamageFireCeilHitSpeed() * ceilingNormal;
            sead::Vector3f moveDir = {0.0f, 0.0f, 0.0f};
            if (!mIsDamageFireWall) {
                mPlayerInput->calcMoveDirection(&moveDir, -ceilingNormal);
            } else {
                moveDir = rs::getCollidedWallNormal(mPlayerCollider);
            }
            bool isNearZero = al::isNearZero(moveDir, 0.001f);
            auto parent = getParent();
            sead::Vector3f result = {};
            sead::Vector3f* velocity = &result;
            if (!isNearZero) {
                result = moveSpeed * moveDir;
                result += parallel;
            } else {
                velocity = &parallel;
            }
            al::setVelocity(parent, *velocity);
            mPlayerActionAirMoveCtrl->setup(mPlayerConst->getDamageFireJumpMoveSpeed(), mPlayerConst->getDamageFireJumpMoveSpeed(), 0, 0.0f,
                                            mPlayerConst->getDamageFireGravity(), mIsDamageFireWall ? 10 : 0, mPlayerConst->getJumpInertiaRate());
        }
    }

    mPlayerActionAirMoveCtrl->update();
    if (rs::isOnGround(getParent(), mPlayerCollider)) {
        sead::Vector3f normalH = {0.0f, 0.0f, 0.0f};
        al::alongVectorNormalH(&normalH, al::getVelocity(getParent()), -al::getGravity(getParent()), rs::getCollidedGroundNormal(mPlayerCollider));
        if (!mPlayerInput->isMove())
            normalH = {0.0f, 0.0f, 0.0f};

        auto parent = getParent();
        sead::Vector3f velocity = normalH - rs::getCollidedGroundNormal(mPlayerCollider) * mPlayerConst->getGravity();
        al::setVelocity(parent, velocity);
        al::setNerve(this, &Jump2nd);
    }
}

void PlayerStateDamageFire::exeJump2nd() {
    if (al::isFirstStep(this)) {
        mPlayerAnimator->startAnim("FireRunStart");

        al::startHitReaction(getParent(), "あちちジャンプ(バウンド)");
        sead::Vector3f groundNormal = {0.0f, 0.0f, 0.0f};
        rs::calcGroundNormalOrGravityDir(&groundNormal, getParent(), mPlayerCollider);
        sead::Vector3f moveDir = {0.0f, 0.0f, 0.0f};
        mPlayerInput->calcMoveDirection(&moveDir, groundNormal);

        if (!al::isNearZero(moveDir, 0.001)) {
            sead::Vector3f vertical = {0.0f, 0.0f, 0.0f};
            sead::Vector3f parallel = {0.0f, 0.0f, 0.0f};

            al::separateVectorParallelVertical(&parallel, &vertical, groundNormal, al::getVelocity(getParent()));
            auto parent = getParent();
            sead::Vector3f velocity = vertical.length() * moveDir + parallel;
            // sead::Vector3CalcCommon<f32>::multScalarAdd(velocity, vertical.length(), moveDir, parallel);  does not match
            al::setVelocity(parent, velocity);
        }
        mPlayerActionAirMoveCtrl->setup(mPlayerConst->getDamageFireJumpMoveSpeed(), mPlayerConst->getDamageFireJumpMoveSpeed(), 0,
                                        mPlayerConst->getDamageFireJumpPower2nd(), mPlayerConst->getDamageFireGravity(), 0,
                                        mPlayerConst->getJumpInertiaRate());
    }
    mPlayerActionAirMoveCtrl->update();
    if (rs::isOnGround(getParent(), mPlayerCollider)) {
        mDamageFireTimer = 0;
        mPlayerActionGroundMoveCtrl->appear();
        al::setNerve(this, &nrvPlayerStateDamageFire.Run);
    }
}

void PlayerStateDamageFire::exeRun() {
    if (al::isFirstStep(this)) {
        if (!mPlayerAnimator->isAnim("FireRun")) {
            mPlayerAnimator->startAnim("FireRun");
            mPlayerAnimator->setAnimRate(mPlayerConst->getDamageFireRunSpeed() * mPlayerConst->getDamageFireRunAnimRate());
        }
        rs::resetJudge(mPlayerJudgeSpeedCheckFall);
        mPlayerActionGroundMoveCtrl->reset(mPlayerActionGroundMoveCtrl->getGroundNormal());
        mFireRunBrakeFrame = mPlayerConst->getDamageFireRunBrakeFrame();
    }
    mPlayerActionGroundMoveCtrl->update();

    if (!mPlayerInput->isMove()) {
        f32 fireRunSpeed = mPlayerConst->getDamageFireRunSpeed();
        al::tryAddVelocityLimit(getParent(), fireRunSpeed * mPlayerActionGroundMoveCtrl->get_field_90(), fireRunSpeed);
        f32 fireRunBrakeFrame = mPlayerConst->getDamageFireRunBrakeFrame();
        mFireRunBrakeFrame = al::converge(mFireRunBrakeFrame, fireRunBrakeFrame, 1);
        f32 rate = al::calcRate01(mFireRunBrakeFrame, 0.0f, mPlayerConst->getDamageFireRunBrakeFrame());
        f32 scale = sead::Mathf::clamp(1.0f - al::easeOut(rate), 0.0f, 1.0f);
        al::scaleVelocityExceptDirection(getParent(), mPlayerActionGroundMoveCtrl->getGroundNormal(), scale);
    } else {
        f32 fireRunSpeed = mPlayerConst->getDamageFireRunSpeed();
        al::tryAddVelocityLimit(getParent(), fireRunSpeed * mPlayerActionGroundMoveCtrl->get_field_90(), fireRunSpeed);
        mFireRunBrakeFrame = 0;
    }

    if (rs::updateJudgeAndResult(mPlayerJudgeSpeedCheckFall))
        return al::setNerve(this, &nrvPlayerStateDamageFire.Fall);

    if (!al::isLessStep(this, mPlayerConst->getDamageFireRunTime()))
        kill();
}

void PlayerStateDamageFire::exeFall() {
    if (al::isFirstStep(this)) {
        mPlayerActionAirMoveCtrl->setup(mPlayerConst->getDamageFireJumpMoveSpeed(), mPlayerConst->getDamageFireJumpMoveSpeed(), 0, 0.0f,
                                        mPlayerConst->getGravityAir(), 0, mPlayerConst->getJumpInertiaRate());
    }
    mPlayerActionAirMoveCtrl->update();
    if (rs::isOnGround(getParent(), mPlayerCollider)) {
        mPlayerActionGroundMoveCtrl->appear();
        al::setNerve(this, &nrvPlayerStateDamageFire.Run);
    }
}

void PlayerStateDamageFire::exeDead() {
    if (al::isFirstStep(this)) {
        if (((u8*)mPlayerAnimator)[0x1a2])  // checks if field_1a2 is true
            mPlayerAnimator->endSubAnim();

        mPlayerAnimator->startAnim("DeadFire");
        auto parent = getParent();
        rs::slerpUp(parent, -al::getGravity(parent), 1.0f, 0.0f);
        rs::faceToCamera(parent);
    }
    if (mPlayerAnimator->isAnimEnd())
        kill();
}