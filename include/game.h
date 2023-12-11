#ifndef GAME_H_GUARD
#define GAME_H_GUARD

#include <SDL2/SDL.h>
#include <scene.h>

class Game {
public:
  Game(const char *title, int width, int height, Uint32 flags);
  Game(Game &&) = default;
  Game(const Game &) = default;
  Game &operator=(Game &&) = default;
  Game &operator=(const Game &) = default;
  ~Game();

  void events(void);
  void update(void);
  void render(void);

  bool isRunning() const;

  Scene *scene;
  SDL_Renderer *renderer;

private:
  SDL_Window *window;
  bool running;
};

extern Game *game;

#endif // !GAME_H_GUARD
