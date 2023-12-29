#include "sprite.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Sprite::Sprite(const char *path) {
  SDL_Surface *surface = IMG_Load(path);
  if (!surface)
    return;

  texture = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
}

Sprite::~Sprite() {
  if (texture)
    SDL_DestroyTexture(texture);
}

void Sprite::Render(SDL_Renderer *renderer, const SDL_Rect *src,
                    const SDL_Rect *dest) {
  SDL_RenderCopy(renderer, texture, src, dest);
}
