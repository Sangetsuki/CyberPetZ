#include "main_menu.h"
#include "game.h"
#include "gui.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include "sprite.h"
#include <cassert>
#include <raylib.h>

using namespace gui;

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};

static bool lightsoff = false;
static auto monster = &gSaveData->monster;
static Sprite *monSprite = nullptr;
static double lasttime = 0.0;

static const Button eatbutton({100, 100, 150, 25}, "Alimentar", [] {
  monster->hungry -= 10;
  if (monster->hungry > 100)
    monster->hungry = 0;
});

static const Button drinkbutton({100, 150, 150, 25}, "Dar agua", [] {
  monster->thirsty -= 10;
  if (monster->thirsty > 100)
    monster->thirsty = 0;
});

static const Button hbutton({100, 200, 150, 25}, "Dar remedio", [] {
  monster->healthy += 10;
  if (monster->healthy > 100)
    monster->healthy = 100;
});

static void MainMenuUpdate(void) {
  double now = GetTime();
  if (now - lasttime >= 1.0) {
    monster->step();
    lasttime = now;
  }
}

static void MainMenuRender() {
  monSprite->Render(200, 200);
  RenderVerticalProgressBar(600, 200, 20, 200,
                            static_cast<float>(monster->healthy) / 100, RED);
  RenderVerticalProgressBar(650, 200, 20, 200,
                            static_cast<float>(monster->hungry) / 100, GREEN);
  RenderVerticalProgressBar(700, 200, 20, 200,
                            static_cast<float>(monster->thirsty) / 100, BLUE);
  eatbutton.render();
  drinkbutton.render();
  hbutton.render();
  DrawText(monster->name, 260, 460, 20, BLACK);
}

static void MainMenuClean(void) {
  lightsoff = false;
  delete monSprite;
  game->scene = nullptr;
}

static void MainMenuHandleEvents() {
  if (IsKeyReleased(KEY_SPACE)) {
    lightsoff = !lightsoff;
  } else if (IsKeyReleased(KEY_Q)) {
    MainMenuClean();
    game->scene = &TitleScreen;
    return;
  }
  eatbutton.handleClick();
  drinkbutton.handleClick();
  hbutton.handleClick();
}

const Scene MainMenuScene(MainMenuHandleEvents, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from title screen
void SetupMainMenu() {
  monSprite = new Sprite(assets[monster->species - 1]);
  assert(monSprite != nullptr);
  game->scene = &MainMenuScene;
}
