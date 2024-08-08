#include "gui.h"
#include "main_menu.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include <raylib.h>

static const Rectangle boxes[] = {{150, 30, 400, 200}, {200, 300, 550, 50}};

static Color color = BLACK;

static unsigned int counter = 0;

static const char *gamename = "CyberPetZ";
static const char *current = nullptr;

static bool typing = false;
static char newname[12];
static size_t currentindex = 0;

static const gui::Button new_game_btn({30, 300, 400, 50}, "Novo Jogo",
                                      [] { typing = true; });

static gui::TextBox
    new_monster_name(boxes[1], 12,
                     "Digite o nome do seu CyberPet:", [](std::string newname) {
                       typing = false;
                       gSaveData->monster = Monster(newname.c_str());
                       gSaveData->monster.species =
                           (MonsterID)((GetMouseX() * GetMouseY()) % 2 + 1);
                       gSaveExists = true;
                       SetupMainMenu();
                     });

static const gui::Button continue_btn({30, 400, 400, 50}, "Continuar", [] {
  if (!typing && gSaveExists)
    SetupMainMenu();
});

static void TitleScreenHandleEvents() {
  continue_btn.handleClick();
  new_game_btn.handleClick();
}

static void TitleScrenUpdater(void) {
  counter++;

  if (typing) {
    if (IsKeyPressed(KEY_ESCAPE)) {
      typing = false;
      new_monster_name.destroy();
    } else {
      new_monster_name.update();
    }
  }

  if (counter % 20 == 0)
    current = TextSubtext(gamename, 0, counter % 10);
}

static void TitleScreenRender() {
  DrawText(current, boxes[0].x + 10, boxes[0].y + 4, 40, BLACK);
  new_game_btn.render();
  if (gSaveExists) {
    continue_btn.render();
  }
  if (typing) {
    new_monster_name.render();
  }
}

const Scene TitleScreen(TitleScreenHandleEvents, TitleScrenUpdater,
                        TitleScreenRender);
