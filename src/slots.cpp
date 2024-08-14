#include "game.h"
#include "main_menu.h"
#include "save.h"
#include "scene.h"
#include <raylib.h>
#include <raymath.h>

static void SlotsMinigameRender(void);
static void SlotsMinigameUpdate(void);
static void SlotsMinigameUpdateEvents(void);

static int *chips = &gSaveData->chips;
static char slots[3][3] = {0};
static int rounds[3] = {0};
static bool bet = false;

static const Scene SlotsMinigame(SlotsMinigameUpdateEvents, SlotsMinigameUpdate,
                                 SlotsMinigameRender);

static void SlotsMinigameUpdateEvents(void) {
  if (IsKeyReleased(KEY_Q)) {
    SetupMainMenu();
    return;
  }
  if (IsKeyReleased(KEY_SPACE)) {
    if (!bet && *chips - 3 < 0) {
      return;
    }
    for (int i = 0; i < 3; i++) {
      if (rounds[i] != 0) {
        for (int j = i + 1; j < 3; j++) {
          rounds[j] -= rounds[i];
        }
        rounds[i] = 0;
        return;
      }
    }
    rounds[0] = GetRandomValue(100, 150);
    rounds[1] = rounds[0] + GetRandomValue(20, 30);
    rounds[2] = rounds[1] + GetRandomValue(20, 30);
    *chips -= 3;
    bet = true;
  }
}

static float checkprize() {
  float multiplier = 1.0;

  for (int i = 0; i < 3; i++) {
    if (slots[0][i] == slots[1][i] && slots[1][i] == slots[2][i]) {
      multiplier += 0.5;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (slots[i][0] == slots[i][1] && slots[i][1] == slots[i][2]) {
      multiplier += 0.5;
    }
  }

  if (slots[0][0] == slots[1][1] && slots[1][1] == slots[2][2]) {
    multiplier += 0.5;
  }
  if (slots[0][2] == slots[1][1] && slots[1][1] == slots[2][0]) {
    multiplier += 0.5;
  }

  return multiplier == 1.0 ? 0 : multiplier;
}

static void SlotsMinigameUpdate(void) {
  for (int i = 0; i < 3; i++) {
    if (rounds[i] > 0) {
      /*char tmp = slots[i][0];
      slots[i][0] = slots[i][2];
      slots[i][2] = slots[i][1];
      slots[i][1] = tmp;*/
      for (int j = 0; j < 3; j++) {
        slots[i][j] = GetRandomValue('a', 'f');
      }
      rounds[i]--;
    }
  }
  if (rounds[2] == 0 && bet == true) {
    *chips += floor(3.0 * checkprize());
    bet = false;
  }
}

static void SlotsMinigameRender(void) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      DrawText(TextFormat("%c", slots[i][j]), 320 + 40 * (i), 320 + 40 * j, 20,
               BLACK);
    }
  }
  DrawText(TextFormat("moedas: %d", *chips), 700, 4, 18, BLACK);
}

void SlotsMinigameSetup() {
  for (int i = 0; i < 3; i++) {
    slots[i][0] = 'a';
  }
  for (int i = 0; i < 3; i++) {
    slots[i][1] = 'b';
  }
  for (int i = 0; i < 3; i++) {
    slots[i][2] = 'c';
  }
  game->scene = &SlotsMinigame;
}
