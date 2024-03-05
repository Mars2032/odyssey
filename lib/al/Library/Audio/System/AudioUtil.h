#pragma once

namespace al {
class IUseAudioKeeper;

void deactivateAudioEventController(const al::IUseAudioKeeper*);
void activateAudioEventController(const al::IUseAudioKeeper*);
void banAudioEventActivation(const al::IUseAudioKeeper*);
void allowAudioEventActivation(const al::IUseAudioKeeper*);
void startAndStopBgmInCurPosition(const al::IUseAudioKeeper*, bool);
}  // namespace al