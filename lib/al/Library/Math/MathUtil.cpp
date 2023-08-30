#pragma once

#include <al/Library/Math/MathUtil.h>

namespace al {

void rotateVectorDegree(sead::Vector3f* out, const sead::Vector3f& dir, const sead::Vector3f& axis, float angle) {
    sead::Quatf q;
    sead::QuatCalcCommon<f32>::setAxisAngle(q, axis, angle);
    sead::Vector3CalcCommon<f32>::rotate(*out, q, dir);
}

}  // namespace al