#include "game.h"
#include "scene.h"
#include <raylib.h>

double start;
Game *game = nullptr;

Game::Game(const char *title, int width, int height, unsigned int flags) {
  SetConfigFlags(flags);
  InitWindow(width, height, title);

  running = true;
  scene = new Scene(TitleScreen);

  ClearBackground(WHITE);
}

Game::~Game() {
  delete scene;
  CloseWindow();
}

void Game::render(void) {
  ClearBackground(WHITE);
  BeginDrawing();

  DrawFPS(0, 0);
  scene->render();

  EndDrawing();
}

void Game::update(void) { scene->update(); }

void Game::events(void) { scene->events(); }

bool Game::isRunning() const { return running && !WindowShouldClose(); }
