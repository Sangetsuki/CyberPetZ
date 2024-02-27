#include "gui.h"
#include "main_menu.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#include <raylib.h>

static const Rectangle boxes[] = {{150, 30, 400, 200}, {200, 300, 350, 50}};

static Color color = {0x00, 0x00, 0x00};

static unsigned int counter = 0;

static const char *gamename = "CyberPetZ";
static const char *current = nullptr;

static bool typing = false;
static char newname[12];
static size_t currentindex = 0;

static const gui::Button new_game_btn({30, 300, 400, 50}, "Novo Jogo",
                                      [] { typing = true; });

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
    int key = GetCharPressed();
    while (key > 0) {
      if ((key >= 32) && (key <= 125) && currentindex < 12) {
        newname[currentindex] = key;
        newname[++currentindex] = 0;
      }
      key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
      typing = false;
      newname[0] = 0;
      currentindex = 0;
    } else if (IsKeyPressed(KEY_BACKSPACE) && currentindex > 0) {
      newname[--currentindex] = 0;
    } else if (IsKeyPressed(KEY_ENTER) && currentindex != 0) {
      typing = false;
      gSaveData->monster = Monster(newname);
      gSaveData->monster.species = MONID_PENGU;
      gSaveExists = true;
      SetupMainMenu();
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
    DrawRectangle(boxes[1].x, boxes[1].y - 20, boxes[1].width, 20, WHITE);
    DrawRectangleLines(boxes[1].x, boxes[1].y - 20, boxes[1].width, 20, BLACK);
    DrawText("Digite o nome do seu novo CyberPet:", boxes[1].x + 2,
             boxes[1].y - 20 + 2, 18, BLACK);
    DrawRectangleRec(boxes[1], WHITE);
    DrawRectangleLinesEx(boxes[1], 1.0, BLACK);
    DrawText(newname, boxes[1].x + 2, boxes[1].y + 2, 40, BLACK);
  }
}

const Scene TitleScreen(TitleScreenHandleEvents, TitleScrenUpdater,
                        TitleScreenRender);
