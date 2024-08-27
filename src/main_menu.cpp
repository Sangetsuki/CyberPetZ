#include "main_menu.h"
#include "game.h"
#include "gui.h"
#include "minigames.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include "sprite.h"
#include <cassert>
#include <raylib.h>

using namespace gui;

static bool lightsoff = false;
static auto monster = &gSaveData->monster;
static Sprite *monSprite = nullptr;
static double lasttime = 0.0;
static bool text = false;

static void MainMenuClean(void);

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

struct {
  Rectangle border;
  Button games[4];
  bool active;
  void render() {
    DrawRectangleRec(border, WHITE);
    DrawRectangleLinesEx(border, 1.0, BLACK);
    for (auto &button : games) {
      button.render();
    }
  }
  void events() {
    for (auto &button : games) {
      button.handleClick();
    }
  }
} MinigamesBox = {{60, 120, 680, 240},
                  {Button({70, 120 + 10, 120, 50}, "RPG",
                          [] {
                            MainMenuClean();
                            RpgMinigameSetup();
                          }),
                   Button({200, 120 + 10, 120, 50}, "Pong",
                          [] {
                            MainMenuClean();
                            SetupPongMinigame();
                          }),
                   Button({330, 120 + 10, 120, 50}, "Slots",
                          [] {
                            MainMenuClean();
                            SlotsMinigameSetup();
                          }),
                   Button({460, 120 + 10, 120, 50}, "Xadrez",
                          [] {
                            MainMenuClean();
                            SetupChessMinigame();
                          })},
                  false};

static const Button playbutton({100, 250, 150, 25}, "Jogar",
                               [] { MinigamesBox.active = true; });

static void MainMenuUpdate(void) {
  double now = GetTime();
  if (now - lasttime >= 1.0 && !MinigamesBox.active) {
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
  playbutton.render();
  DrawText(monster->name, 260, 460, 20, BLACK);
  if (MinigamesBox.active) {
    MinigamesBox.render();
  }
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
    if (MinigamesBox.active) {
      MinigamesBox.active = false;
    } else {
      MainMenuClean();
      game->scene = &TitleScreen;
    }
    return;
  }
  if (MinigamesBox.active) {
    MinigamesBox.events();
  } else {
    eatbutton.handleClick();
    drinkbutton.handleClick();
    hbutton.handleClick();
    playbutton.handleClick();
  }
}

const Scene MainMenuScene(MainMenuHandleEvents, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from title screen
void SetupMainMenu() {
  monSprite = createSaveMonSprite();
  assert(monSprite != nullptr);
  game->scene = &MainMenuScene;
}
