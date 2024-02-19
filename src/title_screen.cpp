#include "main_menu.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include <raymath.h>

static const Rectangle boxes[] = {{150, 30, 400, 200},
                                  {30, 300, 400, 50},
                                  {30, 400, 400, 50},
                                  {200, 300, 350, 50}};

static Color color = {0x00, 0x00, 0x00};

static unsigned int counter = 0;

static const char *gamename = "CyberPetZ";
static const char *current = nullptr;

static bool typing = false;
static char newname[12];
static size_t currentindex = 0;

static void TitleScreenHandleEvents() {
  Vector2 mousepos = GetMousePosition();
  if (!typing && gSaveExists && CheckCollisionPointRec(mousepos, boxes[2]) &&
      IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { // CONTINUE
    SetupMainMenu();
  } else if (CheckCollisionPointRec(mousepos, boxes[1]) &&
             IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { // NEW GAME
    typing = true;
  }
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

  if (counter % 10 != 0)
    return;
  current = TextSubtext(gamename, 0, counter % 9);
}

static void TitleScreenRender() {
  DrawRectangleLinesEx(boxes[0], 1.0, BLACK);
  DrawText(current, boxes[0].x + 10, boxes[0].y + 4, 40, BLACK);
  DrawRectangleLinesEx(boxes[1], 1.0, BLACK);
  DrawText("Novo Jogo", boxes[1].x + 10, boxes[1].y + 4, 40, BLACK);
  if (gSaveExists) {
    DrawRectangleLinesEx(boxes[2], 1.0, BLACK);
    DrawText("Continuar", boxes[2].x + 10, boxes[2].y + 4, 40, BLACK);
  }
  if (typing) {
    DrawRectangle(boxes[3].x, boxes[3].y - 20, boxes[3].width, 20, WHITE);
    DrawRectangleLines(boxes[3].x, boxes[3].y - 20, boxes[3].width, 20, BLACK);
    DrawText("Digite o nome do seu novo CyberPet:", boxes[3].x + 2,
             boxes[3].y - 20 + 2, 18, BLACK);
    DrawRectangleRec(boxes[3], WHITE);
    DrawRectangleLinesEx(boxes[3], 1.0, BLACK);
    DrawText(newname, boxes[3].x + 2, boxes[3].y + 2, 40, BLACK);
  }
}

const Scene TitleScreen(TitleScreenHandleEvents, TitleScrenUpdater,
                        TitleScreenRender);
