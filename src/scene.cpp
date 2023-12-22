#include "scene.h"

Scene::Scene(EventsFunction ehndlr, UpdateFunction updtr, RenderFunction rndr)
    : updater(updtr), renderer(rndr), eHandler(ehndlr) {}

Scene::~Scene() {}

void Scene::events(SDL_Event *e) const {
  if (eHandler)
    eHandler(e);
}

void Scene::update(void) const {
  if (updater)
    updater();
}

void Scene::render(SDL_Renderer *ren) const {
  if (renderer)
    renderer(ren);
}
