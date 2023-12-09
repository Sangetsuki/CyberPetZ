#include <SDL2/SDL.h>
#include <game.h>

// TODO: command line arguments (e.g. fullscreen)
int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  Game game("CyberPetZ", 800, 640, 0);

  // TODO: Limit frame rate to 60 FPS
  while (game.isRunning()) {
    game.events();
    game.update();
    game.render();
  }

  SDL_Quit();
  return 0;
}
