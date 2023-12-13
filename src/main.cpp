#include "game.h"
#include "save.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <getopt.h>
#include <iostream>

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

  game = new Game("CyberPetZ", 800, 640, flags);
  gSaveData->readFile();
  if (gSaveExists) {
    std::time_t now = std::time(nullptr);
    std::time_t delta = now - gSaveData->closed;
    char timestring[100];
    struct tm *ptm = gmtime(&delta);
    std::strftime(timestring, 100,
                  "Time since last save: %H hours %M minutes %S seconds\n",
                  ptm);
    std::cout << timestring;
  }

  // TODO: Limit frame rate to 60 FPS
  while (game->isRunning()) {
    game->events();
    game->update();
    game->render();
  }

  if (gSaveExists) {
    gSaveData->closed = std::time(nullptr);
    gSaveData->writeFile();
  }

  delete game;

  IMG_Quit();
  SDL_Quit();
  return 0;
}
