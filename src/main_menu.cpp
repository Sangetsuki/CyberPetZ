#include "main_menu.h"
#include "game.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include <SDL_image.h>

extern unsigned int start;
static SDL_Texture *texture;
static const SDL_Rect src{0, 0, 1024, 1024};
static const SDL_Rect dest{272, 192, 256, 256};

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};

static void MainMenuUpdate(void) {
  unsigned int now = SDL_GetTicks();

  if ((now - start) % 1000 == 0) {
    gSaveData->monster.step();
  }
}

static void render_mon_healthbar(SDL_Renderer *renderer) {
  const SDL_Rect health_bar = {600, 400 - 2 * gSaveData->monster.healthy, 20,
                               gSaveData->monster.healthy * 2};
  const SDL_Rect health_box = {600, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &health_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &health_box);
}

static void render_mon_hungry(SDL_Renderer *renderer) {
  SDL_Rect hungry_bar = {650, 400 - 2 * gSaveData->monster.hungry, 20,
                         gSaveData->monster.hungry * 2};
  SDL_Rect hungry_box = {650, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &hungry_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &hungry_box);
}

static void render_mon_thirsty(SDL_Renderer *renderer) {
  SDL_Rect thirsty_bar = {700, 400 - 2 * gSaveData->monster.thirsty, 20,
                          gSaveData->monster.thirsty * 2};
  SDL_Rect thirsty_box = {700, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &thirsty_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &thirsty_box);
}

static void MainMenuRender(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, texture, &src, &dest);
  render_mon_healthbar(renderer);
  render_mon_hungry(renderer);
  render_mon_thirsty(renderer);

  SDL_RenderPresent(renderer);
}

const Scene MainMenuScene(nullptr, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from boot
void SetupMainMenu() {
  SDL_Surface *surface = IMG_Load(assets[gSaveData->monster.species - 1]);
  texture = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  *game->scene = MainMenuScene;
}
