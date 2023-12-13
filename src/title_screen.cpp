#include "main_menu.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <cmath>

static const SDL_Rect boxes[] = {
    {150, 30, 400, 200}, {30, 300, 400, 50}, {30, 400, 400, 50}};

static Uint32 color[] = {0x00, 0x00, 0x00};

static Uint32 counter = 0;

static void TitleScreenHandleEvents(SDL_Event event) {
  SDL_Point mousepos;
  if (event.type == SDL_MOUSEBUTTONUP) {
    SDL_GetMouseState(&mousepos.x, &mousepos.y);
    if (gSaveExists && SDL_PointInRect(&mousepos, boxes + 2) &&
        event.button.button == SDL_BUTTON_LEFT) {
      SetupMainMenu();
    } else if (SDL_PointInRect(&mousepos, boxes + 1) &&
               event.button.button == SDL_BUTTON_LEFT) {
      gSaveData->monster = Monster();
      gSaveData->monster.species = MONID_PENGU;
      gSaveExists = true;
      SetupMainMenu();
    }
  }
}

static void TitleScrenUpdater(void) {
  auto arg = (2 * M_PI / 512) * ((float)counter / 60);
  auto cosine = cos(arg);
  color[0] = 61 * cosine + 137;
  color[1] = 78 * cosine + 87;
  color[2] = 60 * cosine + 141;
  SDL_Log("counter: %d, r: %d, g: %d, b: %d", counter, color[0], color[1],
          color[2]);

  counter++;
}

static void TitleScreenRender(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0xFF);
  SDL_RenderFillRects(renderer, boxes, 1);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRects(renderer, boxes + 1, 1 + gSaveExists);
}

const Scene TitleScreen(TitleScreenHandleEvents, TitleScrenUpdater,
                        TitleScreenRender);
