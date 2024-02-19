#include "main_menu.h"
#include "game.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include "sprite.h"
#include <cassert>
#include <raylib.h>

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};

static bool lightsoff = false;
static auto monster = &gSaveData->monster;
static Sprite *monSprite = nullptr;
static double lasttime = 0.0;

static void MainMenuUpdate(void) {
  double now = GetTime();
  if (now - lasttime >= 1.0) {
    monster->step();
    lasttime = now;
  }
}

static void render_mon_healthbar() {
  const Rectangle health_bar = {600,
                                static_cast<float>(400 - 2 * monster->healthy),
                                20, static_cast<float>(monster->healthy * 2)};
  const Rectangle health_box = {600, 200, 20, 200};

  DrawRectangleRec(health_bar, RED);
  DrawRectangleLinesEx(health_box, 1.0, BLACK);
}

static void render_mon_hungry() {
  const Rectangle hungry_bar = {650,
                                static_cast<float>(400 - 2 * monster->hungry),
                                20, static_cast<float>(monster->hungry * 2)};
  const Rectangle hungry_box = {650, 200, 20, 200};

  DrawRectangleRec(hungry_bar, GREEN);
  DrawRectangleLinesEx(hungry_box, 1.0, BLACK);
}

static void render_mon_thirsty() {
  const Rectangle thirsty_bar = {700,
                                 static_cast<float>(400 - 2 * monster->thirsty),
                                 20, static_cast<float>(monster->thirsty * 2)};
  const Rectangle thirsty_box = {700, 200, 20, 200};

  DrawRectangleRec(thirsty_bar, BLUE);
  DrawRectangleLinesEx(thirsty_box, 1.0, BLACK);
}

static void MainMenuRender() {
  monSprite->Render(200, 200);
  render_mon_healthbar();
  render_mon_hungry();
  render_mon_thirsty();
  DrawText(monster->name, 260, 460, 20, BLACK);
}

static void MainMenuClean(void) {
  lightsoff = false;
  delete monSprite;
}

static void MainMenuHandleEvents() {
  if (IsKeyReleased(KEY_SPACE)) {
    lightsoff = !lightsoff;
  } else if (IsKeyReleased(KEY_Q)) {
    MainMenuClean();
    *game->scene = TitleScreen;
  }
}

const Scene MainMenuScene(MainMenuHandleEvents, MainMenuUpdate, MainMenuRender);

// MainMenu entry point from title screen
void SetupMainMenu() {
  monSprite = new Sprite(assets[monster->species - 1]);
  assert(monSprite != nullptr);
  *game->scene = MainMenuScene;
}
