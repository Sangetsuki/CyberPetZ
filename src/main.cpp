#include "game.h"
#include "save.h"
#include <cassert>
#include <ctime>
#include <getopt.h>
#include <iostream>
#include <raylib.h>

static const option arguments[] = {{"fullscreen", no_argument, NULL, 'f'}};

int main(int argc, char *argv[]) {
  unsigned int flags = 0;

  char c;
  while ((c = getopt_long(argc, argv, "f", arguments, NULL)) != -1) {
    switch (c) {
    case 'f':
      flags |= FLAG_FULLSCREEN_MODE;
    }
  }

  game = new Game("CyberPetZ", 800, 640, flags);
  assert(game);
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

  SetTargetFPS(60);
  SetExitKey(KEY_NULL);
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

  return 0;
}
