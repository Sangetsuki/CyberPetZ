#ifndef FADER_H_GUARD
#define FADER_H_GUARD

#include <SDL2/SDL.h>

namespace fader {
enum FadeMode { FADE_NONE = 0, FADE_OUT, FADE_IN };
void ResetFader(FadeMode mode);
void UpdateFader(void);
void RenderFader(SDL_Renderer *renderer);
void WaitFader(FadeMode mode = FADE_NONE);
bool isFaderActive(void);
}; // namespace fader

#endif
