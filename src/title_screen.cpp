#include "main_menu.h"
#include "scene.h"
#include <SDL2/SDL.h>

static const SDL_Rect boxes[] = {
    {150, 30, 400, 200}, {30, 300, 400, 50}, {30, 400, 400, 50}};

static void TitleScreenHandleEvents(SDL_Event event) {
  SDL_Point mousepos;
  if (event.type == SDL_MOUSEBUTTONUP) {
    SDL_GetMouseState(&mousepos.x, &mousepos.y);
    SDL_Log("mouse: %d, %d", mousepos.x, mousepos.y);
    if (SDL_PointInRect(&mousepos, boxes + 2) &&
        event.button.button == SDL_BUTTON_LEFT) {
      SetupMainMenu();
    }
  }
}

static void TitleScrenUpdater(void) {}

static void TitleScreenRender(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderFillRects(renderer, boxes, 1);
  SDL_RenderDrawRects(renderer, boxes + 1, 2);
}

const Scene TitleScreen(TitleScreenHandleEvents, nullptr, TitleScreenRender);
