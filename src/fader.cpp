#include "fader.h"
#include <SDL2/SDL.h>

static short unsigned int fadercount = 0x00;
static fader::FadeMode fadermode = fader::FADE_NONE;
static const SDL_Rect mask = {0, 0, 800, 640};

void fader::ResetFader(FadeMode mode) {
  fadermode = mode;
  switch (mode) {
  case fader::FADE_OUT:
    fadercount = 0x00;
    break;
  case fader::FADE_IN:
    fadercount = 0xFF;
    break;
  default:
    fadermode = FADE_NONE;
    break;
  }
}

void fader::UpdateFader(void) {
  if (fadermode == FADE_NONE)
    return;

  switch (fadermode) {
  case FADE_OUT:
    if (fadercount == 0xFF) {
      fadermode = FADE_NONE;
      break;
    }
    fadercount++;
    break;
  case FADE_IN:
    if (fadercount == 0x00) {
      fadermode = FADE_NONE;
      break;
    }
    fadercount--;
    break;
  default:
    break;
  }
}

void fader::RenderFader(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, fadercount);
  SDL_RenderFillRect(renderer, &mask);
}

bool fader::isFaderActive(void) { return fadermode != fader::FADE_NONE; }
