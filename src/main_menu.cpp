#include "main_menu.h"
#include "game.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include <SDL_blendmode.h>
#include <SDL_image.h>
#include <SDL_render.h>

extern unsigned int start;
static SDL_Texture *texture;
static const SDL_Rect src{0, 0, 1024, 1024};
static const SDL_Rect dest{272, 192, 256, 256};

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};

static bool lightsoff = false;
static unsigned short int fadecount = 0x00;
#define FADE_NONE 0
#define FADE_OUT 1
#define FADE_IN 2
static unsigned short fademode = FADE_NONE;

static void MainMenuUpdate(void) {
  if (fademode != FADE_NONE) { // fading
    switch (fademode) {
    case FADE_OUT:
      if (fadecount == 0xFF) {
        fademode = FADE_NONE;
        break;
      }
      fadecount++;
      break;
    case FADE_IN:
      if (fadecount == 0x00) {
        fademode = FADE_NONE;
        break;
      }
      fadecount--;
      break;
    }
  }

  unsigned int now = SDL_GetTicks();

  if (!lightsoff && (now - start) % 1000 == 0) {
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
  if (fadecount != 0xFF) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
    render_mon_healthbar(renderer);
    render_mon_hungry(renderer);
    render_mon_thirsty(renderer);
  }
  SDL_Rect mask = {0, 0, 800, 640};
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, fadecount);
  SDL_RenderFillRect(renderer, &mask);

  SDL_RenderPresent(renderer);
}

static void MainMenuHandleEvents(SDL_Event *e) {

  if (e->type != SDL_KEYUP || e->key.state != SDL_RELEASED)
    return;

  SDL_Log("Chegou um evento: %d", e->type);

  switch (e->key.keysym.sym) {
  case SDLK_SPACE:
    lightsoff = !lightsoff;
    if (lightsoff) {
      fadecount = 0x00;
      fademode = FADE_OUT;
    } else {
      fadecount = 0xFF;
      fademode = FADE_IN;
    }
    break;
  default:
    break;
  }
}

const Scene MainMenuScene(MainMenuHandleEvents, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from boot
void SetupMainMenu() {
  SDL_Surface *surface = IMG_Load(assets[gSaveData->monster.species - 1]);
  texture = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  *game->scene = MainMenuScene;
}
