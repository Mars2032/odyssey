#pragma once

#include <prim/seadSafeString.h>

namespace al {
class IUseAudioKeeper;

void startSe(const al::IUseAudioKeeper*, const sead::SafeString&);
}  // namespace al

namespace alSeFunction {
void startSeFromUpperLayerSeKeeper(const al::IUseAudioKeeper*, const char*);
void startListenerPoser(const al::IUseAudioKeeper*, const char*, s32);
void endListenerPoser(const al::IUseAudioKeeper*, const char*, s32);
}  // namespace alSeFunction