#include "main_menu.h"
#include "fader.h"
#include "game.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include "sprite.h"
#include <SDL_image.h>
#include <cassert>

extern unsigned int start;
static const SDL_Rect src{0, 0, 1024, 1024};
static const SDL_Rect dest{272, 192, 256, 256};

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};

static bool lightsoff = false;
static auto monster = &gSaveData->monster;
static Sprite *monSprite = nullptr;

static void MainMenuUpdate(void) {
  unsigned int now = SDL_GetTicks();

  if (!lightsoff && (now - start) % 2000 == 0) {
    monster->step();
  }
}

static void render_mon_healthbar(SDL_Renderer *renderer) {
  const SDL_Rect health_bar = {600, 400 - 2 * monster->healthy, 20,
                               monster->healthy * 2};
  const SDL_Rect health_box = {600, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &health_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &health_box);
}

static void render_mon_hungry(SDL_Renderer *renderer) {
  SDL_Rect hungry_bar = {650, 400 - 2 * monster->hungry, 20,
                         monster->hungry * 2};
  SDL_Rect hungry_box = {650, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &hungry_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &hungry_box);
}

static void render_mon_thirsty(SDL_Renderer *renderer) {
  SDL_Rect thirsty_bar = {700, 400 - 2 * monster->thirsty, 20,
                          monster->thirsty * 2};
  SDL_Rect thirsty_box = {700, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &thirsty_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &thirsty_box);
}

static void MainMenuRender(SDL_Renderer *renderer) {
  monSprite->Render(renderer, &src, &dest);
  render_mon_healthbar(renderer);
  render_mon_hungry(renderer);
  render_mon_thirsty(renderer);
}

static void MainMenuClean(void) {
  lightsoff = false;
  delete monSprite;
}

static void MainMenuHandleEvents(SDL_Event *e) {
  if (e->type != SDL_KEYUP || e->key.state != SDL_RELEASED)
    return;

  switch (e->key.keysym.sym) {
  case SDLK_SPACE:
    lightsoff = !lightsoff;
    fader::ResetFader(lightsoff ? fader::FADE_OUT : fader::FADE_IN);
    break;
  case SDLK_q:
    fader::ResetFader(fader::FADE_OUT);
    MainMenuClean();
    *game->scene = TitleScreen;
    fader::ResetFader(fader::FADE_IN);
    break;
  case SDLK_h:
    if (monster->healthy < 100)
      monster->healthy++;
    break;
  case SDLK_f:
    if (monster->hungry > 0)
      monster->hungry--;
    break;
  case SDLK_t:
    if (monster->thirsty > 0)
      monster->thirsty--;
    break;
  default:
    break;
  }
}

const Scene MainMenuScene(MainMenuHandleEvents, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from title screen
void SetupMainMenu() {
  fader::ResetFader(fader::FADE_OUT);
  monSprite = new Sprite(assets[monster->species - 1]);
  assert(monSprite != nullptr);
  *game->scene = MainMenuScene;
  fader::ResetFader(fader::FADE_IN);
}
