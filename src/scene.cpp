#include "scene.h"

Scene::Scene(EventsFunction ehndlr, UpdateFunction updtr, RenderFunction rndr)
    : updater(updtr), renderer(rndr), eHandler(ehndlr) {}

Scene::~Scene() {}

void Scene::events() const {
  if (eHandler)
    eHandler();
}

void Scene::update(void) const {
  if (updater)
    updater();
}

void Scene::render() const {
  if (renderer)
    renderer();
}
