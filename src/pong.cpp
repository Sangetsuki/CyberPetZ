#include "game.h"
#include "main_menu.h"
#include "scene.h"
#include <raylib.h>
#include <raymath.h>

#define BAR_VEL 8

static void PongMinigameRender(void);
static void PongMinigameUpdate(void);
static void PongMinigameEvents(void);

enum PositionIndex { BALL = 0, PLAYER_BAR, CPU_BAR, Index_End };
static const Vector2 sizes[Index_End] = {{5, 5}, {15, 50}, {15, 50}};
static Vector2 position[Index_End] = {{395, 315}, {10, 295}, {775, 295}};
static Vector2 velocity[Index_End] = {{0, 0}, {0, 0}, {0, 0}};
static int scores[2] = {0, 0};
static bool started = false;
static bool end() { return scores[0] == 5 || scores[1] == 5; }

static const Scene PongMinigame(PongMinigameEvents, PongMinigameUpdate,
                                PongMinigameRender);

void SetupPongMinigame() { game->scene = &PongMinigame; }

static void PongMinigameEvents() {
  if (end() && IsKeyDown(KEY_SPACE)) {
    scores[0] = 0;
    scores[1] = 0;
    position[BALL] = {395, 315};
    position[PLAYER_BAR].y = 295;
    position[CPU_BAR].y = 315;
    velocity[CPU_BAR] = Vector2Zero();
    started = false;
    SetupMainMenu();
    return;
  }

  if (IsKeyDown(KEY_DOWN)) {
    velocity[PLAYER_BAR].y = BAR_VEL;
  } else if (IsKeyDown(KEY_UP)) {
    velocity[PLAYER_BAR].y = -BAR_VEL;
  } else if (!IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) {
    velocity[PLAYER_BAR].y = 0;
  }
  // COOP
  /*if (IsKeyDown(KEY_S)) {
    velocity[CPU_BAR].y = BAR_VEL;
  } else if (IsKeyDown(KEY_W)) {
    velocity[CPU_BAR].y = -BAR_VEL;
  } else if (!IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) {
    velocity[CPU_BAR].y = 0;
  }*/
  if (!started && IsKeyDown(KEY_SPACE)) {
    float angle;
    do {
      angle = GetRandomValue(-5 * PI / 12 - PI * ((scores[0] + scores[1]) % 2),
                             5 * PI / 12 + PI * ((scores[0] + scores[1]) % 2));
    } while (angle == 0);
    velocity[BALL] = Vector2Rotate({BAR_VEL, 0}, angle);
    started = true;
  }
};

static void PongMinigameUpdate() {
  if (scores[0] == 5 || scores[1] == 5) {
    return;
  }
  if (started) {
    int signal = 1;
    if (position[BALL].y < position[CPU_BAR].y + sizes[CPU_BAR].y / 2) {
      signal = -1;
    } else if (position[BALL].y == position[CPU_BAR].y + sizes[CPU_BAR].y / 2) {
      signal = 0;
    }
    velocity[CPU_BAR].y = BAR_VEL * signal;
  }

  for (int i = 0; i < Index_End; i++) {
    position[i].x += velocity[i].x;
    position[i].y += velocity[i].y;
    if (position[i].x < 0) {
      position[i].x = 0;
    }
    if (position[i].x + sizes[i].x > GetRenderWidth()) {
      position[i].x = GetRenderWidth();
    }
    if (position[i].y < 0) {
      position[i].y = 0;
    }
    if (position[i].y + sizes[i].y > GetRenderHeight()) {
      position[i].y = GetRenderHeight() - sizes[i].y;
    }
  }

  Rectangle rect[Index_End] = {
      {position[BALL].x, position[BALL].y, 5, 5},
      {position[PLAYER_BAR].x, position[PLAYER_BAR].y, 15, 50},
      {position[CPU_BAR].x, position[CPU_BAR].y, 15, 50},
  };

  if (CheckCollisionRecs(rect[BALL], rect[PLAYER_BAR]) ||
      CheckCollisionRecs(rect[BALL], rect[CPU_BAR])) {
    velocity[BALL].x *= -1;
    velocity[BALL] = Vector2Scale(velocity[BALL], 1.1);
  }

  if (position[BALL].y <= 0 ||
      position[BALL].y + sizes[BALL].y == GetRenderHeight()) {
    velocity[BALL].y *= -1;
  }

  if (position[BALL].x <= 0) {
    position[BALL].x = 395;
    position[BALL].y = 315;
    velocity[BALL] = {0, 0};
    scores[1]++;
    started = false;
  }
  if (position[BALL].x >= GetRenderWidth() - sizes[BALL].x) {
    position[BALL].x = 395;
    position[BALL].y = 315;
    velocity[BALL] = {0, 0};
    scores[0]++;
    started = false;
  }
};

static void PongMinigameRender() {
  DrawRectangleV(position[PLAYER_BAR], sizes[PLAYER_BAR], BLACK);
  DrawRectangleV(position[CPU_BAR], sizes[CPU_BAR], BLACK);
  DrawRectangleV(position[BALL], sizes[BALL], BLACK);
  DrawText(TextFormat("%d\t|\t%d", scores[0], scores[1]), 300, 20, 40, BLACK);
  DrawText("Você\t\tOponente", 254, 55, 30, BLACK);

  if (end()) {
    DrawText(TextFormat("O vencedor foi %s!\nPrecione espaço para sair.",
                        scores[0] == 5 ? "você" : "o oponente"),
             240, 315, 24, GRAY);
  } else if (!started) {
    DrawText("Aperte espaço para começar.", 240, 315, 24, GRAY);
  }
};
