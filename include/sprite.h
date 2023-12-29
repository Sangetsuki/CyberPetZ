#ifndef SPRITE_H_GUARD
#define SPRITE_H_GUARD

#include <SDL2/SDL.h>

class Sprite {
public:
  Sprite(const char *path);
  Sprite(Sprite &&) = default;
  Sprite(const Sprite &) = default;
  Sprite &operator=(Sprite &&) = default;
  Sprite &operator=(const Sprite &) = default;
  ~Sprite();

  void Render(SDL_Renderer *renderer, const SDL_Rect *src,
              const SDL_Rect *dest);

private:
  SDL_Texture *texture;
};

#endif // !SPRITE_H_GUARD
