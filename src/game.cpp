#include "game.h"
#include "scene.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>

unsigned int start;
Game *game = nullptr;

Game::Game(const char *title, int width, int height, Uint32 flags) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, flags);
  assert(window != nullptr);
  renderer = SDL_CreateRenderer(window, -1, 0);
  assert(renderer != nullptr);
  running = true;
  scene = new Scene(TitleScreen);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game() {
  delete scene;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Game::render(void) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  scene->render(renderer);

  SDL_RenderPresent(renderer);
}

void Game::update(void) { scene->update(); }

void Game::events(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
      return;
    }
    scene->events(&event);
  }
}

bool Game::isRunning() const { return running; }
