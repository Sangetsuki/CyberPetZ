#include <SDL_image.h>
#include <main_menu.h>
#include <monster.h>
#include <scene.h>

static Monster mon = Monster();
extern unsigned int start;
static SDL_Texture *texture;
static const SDL_Rect src{0, 0, 1024, 1024};
static const SDL_Rect dest{272, 192, 256, 256};

static const char *const assets[] = {"assets/pd.png", "assets/pf.png"};

// MainMenu entry point from boot
void SetupMainMenu(Scene *&newscene, SDL_Renderer *renderer) {
  mon.readFromFile();
  SDL_Surface *surface = IMG_Load(assets[mon.species]);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  newscene = &MainMenuScene;
}

void MainMenuUpdate(void) {
  unsigned int now = SDL_GetTicks();

  if ((now - start) % 1000 == 0) {
    mon.step();
  }
}

void render_mon_healthbar(SDL_Renderer *renderer) {
  const SDL_Rect health_bar = {600, 400 - 2 * mon.healthy, 20, mon.healthy * 2};
  const SDL_Rect health_box = {600, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &health_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &health_box);
}

void render_mon_hungry(SDL_Renderer *renderer) {
  SDL_Rect hungry_bar = {650, 400 - 2 * mon.hungry, 20, mon.hungry * 2};
  SDL_Rect hungry_box = {650, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &hungry_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &hungry_box);
}

void render_mon_thirsty(SDL_Renderer *renderer) {
  SDL_Rect thirsty_bar = {700, 400 - 2 * mon.thirsty, 20, mon.thirsty * 2};
  SDL_Rect thirsty_box = {700, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &thirsty_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &thirsty_box);
}

void MainMenuRender(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, texture, &src, &dest);
  render_mon_healthbar(renderer);
  render_mon_hungry(renderer);
  render_mon_thirsty(renderer);

  SDL_RenderPresent(renderer);
}

Scene MainMenuScene(nullptr, MainMenuUpdate, MainMenuRender);
