#include "rpg.h"
#include "game.h"
#include "gui.h"
#include "main_menu.h"
#include "minigames.h"
#include "save.h"
#include "scene.h"
#include "sprite.h"
#include <cassert>
#include <raylib.h>

struct Stats {
  int maxhp;
  int currenthp;
  int atk;
  int def;
};

static struct Stats monStats = {100, gSaveData->monster.healthy,
                                (150 - gSaveData->monster.hungry) / 10,
                                (150 - gSaveData->monster.thirsty) / 10};
static struct Stats enemyStats = {100, 100, 10, 5};

static Sprite *monSprite = nullptr;
static Sprite *enemySprite = nullptr;
static RpgMonster mon;
static void RpgMinigameRender();
static void RpgMinigameUpdater();
static void RpgMinigameEvents();
static void RpgMinigameDestroy();

static gui::Button atk_button({400, 400, 400, 80}, "Bater", [] {

});
static gui::Button item_button({400, 480, 400, 80}, "Item", [] {

});
static gui::Button run_button({400, 560, 400, 80}, "Fugir", [] {

});
RpgMonster::RpgMonster(){};
RpgMonster::~RpgMonster(){};

const Scene RpgMinigame(RpgMinigameEvents, RpgMinigameUpdater,
                        RpgMinigameRender);

static void RpgMinigameRender() {
  Rectangle msgbox = {0, 400, 400, 240};
  DrawRectangleLinesEx(msgbox, 1.0, BLACK);
  DrawText("Você encontrou um esqueleto para batalhar!\nMas esse menu ainda "
           "não funciona :(\nAperte Q para sair.",
           8, 450, 18, BLACK);
  monSprite->Render(100, 50);
  gui::RenderHorizontalProgressBar(
      100, 350, 200, 25,
      static_cast<float>(gSaveData->monster.healthy) / monStats.maxhp, RED);
  enemySprite->Render(450, 60);
  gui::RenderHorizontalProgressBar(
      450, 350, 200, 25,
      static_cast<float>(enemyStats.currenthp) / enemyStats.maxhp, RED);

  atk_button.render();
  item_button.render();
  run_button.render();
}

static void RpgMinigameUpdater() {}
static void RpgMinigameEvents() {
  if (IsKeyReleased(KEY_Q)) {
    RpgMinigameDestroy();
    SetupMainMenu();
  }
}

void RpgMinigameSetup() {
  monSprite = createSaveMonSprite();
  enemySprite = new Sprite("assets/skeleton.png");
  assert(monSprite != nullptr);
  game->scene = &RpgMinigame;
}

static void RpgMinigameDestroy() {
  delete monSprite;
  delete enemySprite;
}
