#ifndef GAME_H_GUARD
#define GAME_H_GUARD

class Scene;

class Game {
public:
  Game(const char *title, int width, int height, unsigned int flags);
  Game(Game &&) = default;
  Game(const Game &) = default;
  Game &operator=(Game &&) = default;
  Game &operator=(const Game &) = default;
  ~Game();

  void events(void);
  void update(void);
  void render(void);

  bool isRunning() const;

  const Scene *scene;

private:
  bool running;
};

extern Game *game;

#endif // !GAME_H_GUARD
