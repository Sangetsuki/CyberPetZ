#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <game.h>

// TODO: command line arguments (e.g. fullscreen)
int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);

  {
    Game game("CyberPetZ", 800, 640, 0);

    // TODO: Limit frame rate to 60 FPS
    while (game.isRunning()) {
      game.events();
      game.update();
      game.render();
    }
  }

  IMG_Quit();
  SDL_Quit();
  return 0;
}
