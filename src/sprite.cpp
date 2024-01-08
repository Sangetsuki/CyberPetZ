#include "sprite.h"
#include <raylib.h>

Sprite::Sprite(const char *path) { texture = LoadTexture(path); }

Sprite::~Sprite() { UnloadTexture(texture); }

void Sprite::Render(float x, float y) {
  DrawTextureEx(texture, {x, y}, 0, 0.25, WHITE);
}
