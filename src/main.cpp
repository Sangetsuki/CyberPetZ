#include <SDL2/SDL.h>
#include <cassert>
#include <monster.h>

// TODO: command line arguments (e.g. fullscreen)
int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *win = SDL_CreateWindow("TamagotchiZ", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 640, 0);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
  assert(win && ren);

  SDL_Event e;
  unsigned int start =
      SDL_GetTicks(); // Every minute, reduce monster health, hungry, thirsty,
                      // dirty and happy. Increase monster age
  // TODO: Limit frame rate to 60 FPS
  // TODO: Real game flow (get events, update, render)
  Monster mon = Monster();
  while (e.type != SDL_QUIT) {
    // Simple logic makes monster sadder and sadder for infinity and beyond
    // (does not checks for overflow);
    unsigned int now = SDL_GetTicks();
    // idk why this runs x4 a frame but hell yeah
    if ((now - start) % 1000 == 0) {
      mon.healthy--;
      mon.dirty++;
      mon.age++;
      mon.happy--;
      mon.hungry++;
      mon.thirsty++;
      SDL_Log(
          "now = %u; start = %u; monster: health = %u; dirty = %u; age = %u\n",
          now, start, mon.healthy, mon.dirty, mon.age);
    }
    SDL_PollEvent(&e);

    SDL_RenderClear(ren);
    // SDL_RenderCopy();
    SDL_RenderPresent(ren);
  }

  SDL_Quit();
  return 0;
}
