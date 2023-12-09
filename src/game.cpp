#include <SDL2/SDL.h>
#include <cassert>
#include <game.h>
#include <monster.h>

Monster mon = Monster();
unsigned int start;

Game::Game(const char *title, int width, int height, Uint32 flags) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, flags);
  assert(window != nullptr);
  renderer = SDL_CreateRenderer(window, -1, 0);
  assert(renderer != nullptr);
  running = true;
  start = SDL_GetTicks();

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Game::render(void) {
  SDL_RenderClear(renderer);
  // render screen
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

Game::~Game() {}
