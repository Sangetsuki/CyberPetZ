#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <game.h>
#include <getopt.h>
#include <unistd.h>

static const option arguments[] = {{"fullscreen", no_argument, NULL, 'f'}};

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);

  Uint32 flags = 0;

  char c;
  while ((c = getopt_long(argc, argv, "f", arguments, NULL)) != -1) {
    switch (c) {
    case 'f':
      flags |= SDL_WINDOW_FULLSCREEN;
    }
  }

  {
    Game game("CyberPetZ", 800, 640, flags);

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
