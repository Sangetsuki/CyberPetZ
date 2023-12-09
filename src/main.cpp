#include <SDL2/SDL.h>
#include <cassert>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *win = SDL_CreateWindow("TamagotchiZ", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 640, 0);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
  assert(win && ren);

  SDL_Event e;

  while (e.type != SDL_QUIT) {
    SDL_PollEvent(&e);
    SDL_RenderClear(ren);
    // SDL_RenderCopy();
    SDL_RenderPresent(ren);
  }

  SDL_Quit();
  return 0;
}
