#include "main_menu.h"
#include "monster.h"
#include "save.h"
#include "scene.h"
#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include <raymath.h>

static const Rectangle boxes[] = {
    {150, 30, 400, 200}, {30, 300, 400, 50}, {30, 400, 400, 50}};

static Color color = {0x00, 0x00, 0x00};

static unsigned int counter = 0;

static const char *gamename = "CyberPetZ";
static const char *current = nullptr;

static void TitleScreenHandleEvents() {
  Vector2 mousepos = GetMousePosition();
  if (gSaveExists && CheckCollisionPointRec(mousepos, boxes[2]) &&
      IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { // CONTINUE
    SetupMainMenu();
  } else if (CheckCollisionPointRec(mousepos, boxes[1]) &&
             IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { // NEW GAME
    gSaveData->monster = Monster();
    gSaveData->monster.species = MONID_PENGU;
    gSaveExists = true;
    SetupMainMenu();
  }
}

static void TitleScrenUpdater(void) {
  counter++;
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
}

const Scene TitleScreen(TitleScreenHandleEvents, TitleScrenUpdater,
                        TitleScreenRender);
