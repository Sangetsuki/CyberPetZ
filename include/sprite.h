#ifndef SPRITE_H_GUARD
#define SPRITE_H_GUARD

#include <raylib.h>

class Sprite {
public:
  Sprite(const char *path);
  Sprite(Sprite &&) = default;
  Sprite(const Sprite &) = default;
  Sprite &operator=(Sprite &&) = default;
  Sprite &operator=(const Sprite &) = default;
  ~Sprite();

  void Render(float x, float y);

private:
  Texture2D texture;
};

Sprite *createSaveMonSprite(void);

#endif // !SPRITE_H_GUARD
