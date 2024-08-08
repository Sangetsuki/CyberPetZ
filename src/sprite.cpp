#include "sprite.h"
#include "save.h"
#include <raylib.h>

static const char *const assets[] = {"assets/pf.png", "assets/pd.png"};
Sprite::Sprite(const char *path) { texture = LoadTexture(path); }

Sprite::~Sprite() { UnloadTexture(texture); }

void Sprite::Render(float x, float y) {
  DrawTextureEx(texture, {x, y}, 0, 0.25, WHITE);
}

Sprite *createSaveMonSprite(void) {
  return new Sprite(assets[gSaveData->monster.species - 1]);
};
