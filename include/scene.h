#ifndef SCENE_H_GUARD
#define SCENE_H_GUARD

#include <functional>

using EventsFunction = std::function<void(void)>;
using UpdateFunction = std::function<void(void)>;
using RenderFunction = std::function<void(void)>;

class Scene {
public:
  Scene(EventsFunction, UpdateFunction, RenderFunction);
  Scene(Scene &&) = default;
  Scene(const Scene &) = default;
  Scene &operator=(Scene &&) = default;
  Scene &operator=(const Scene &) = default;
  ~Scene();

  void events() const;
  void update(void) const;
  void render() const;

  EventsFunction eHandler;
  UpdateFunction updater;
  RenderFunction renderer;
};

void Scene_transition(Scene *newscene);

extern const Scene TitleScreen;

#endif // !SCENE_H_GUARD
