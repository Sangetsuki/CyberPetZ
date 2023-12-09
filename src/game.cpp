#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <game.h>
#include <monster.h>

Monster mon = Monster();
unsigned int start;
SDL_Texture *texture;
SDL_Rect src{0, 0, 1024, 1024};
SDL_Rect dest{272, 192, 256, 256};

Game::Game(const char *title, int width, int height, Uint32 flags) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, flags);
  assert(window != nullptr);
  renderer = SDL_CreateRenderer(window, -1, 0);
  assert(renderer != nullptr);
  running = true;
  start = SDL_GetTicks();

  const char *assets[] = {"assets/pf.png", "assets/pd.png"};
  SDL_Surface *surface = IMG_Load(assets[start % 2]); // Bad but simple random
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Game::~Game() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void render_mon_healthbar(SDL_Renderer *renderer) {
  SDL_Rect health_bar = {600, 400 - 2 * mon.healthy, 20, mon.healthy * 2};
  SDL_Rect health_box = {600, 200, 20, 200};

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
  SDL_Rect thirsty_bar = {700, 400 - 2 * mon.hungry, 20, mon.hungry * 2};
  SDL_Rect thirsty_box = {700, 200, 20, 200};

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &thirsty_bar);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderDrawRect(renderer, &thirsty_box);
}

void Game::render(void) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, texture, &src, &dest);
  render_mon_healthbar(renderer);
  render_mon_hungry(renderer);
  render_mon_thirsty(renderer);

  SDL_RenderPresent(renderer);
}

void Game::update(void) {
  unsigned int now = SDL_GetTicks();
  if ((now - start) % 1000 == 0) {
    mon.step();
  }
}

void Game::events(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  if (event.type == SDL_QUIT) {
    running = false;
    return;
  }
}

bool Game::isRunning() const { return running; }
