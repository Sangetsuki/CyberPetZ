#ifndef SCENE_H_GUARD
#define SCENE_H_GUARD

#include <SDL2/SDL.h>
#include <functional>

using EventsFunction = std::function<void(SDL_Event *)>;
using UpdateFunction = std::function<void(void)>;
using RenderFunction = std::function<void(SDL_Renderer *)>;

class Scene {
public:
  Scene(EventsFunction, UpdateFunction, RenderFunction);
  Scene(Scene &&) = default;
  Scene(const Scene &) = default;
  Scene &operator=(Scene &&) = default;
  Scene &operator=(const Scene &) = default;
  ~Scene();

  void events(SDL_Event *) const;
  void update(void) const;
  void render(SDL_Renderer *) const;

private:
  EventsFunction eHandler;
  UpdateFunction updater;
  RenderFunction renderer;
};

extern const Scene TitleScreen;

#endif // !SCENE_H_GUARD
