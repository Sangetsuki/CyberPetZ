#include <scene.h>

Scene::Scene(EventsFunction ehndlr, UpdateFunction updtr, RenderFunction rndr)
    : updater(updtr), renderer(rndr), eHandler(ehndlr) {}

Scene::~Scene() {}

void Scene::events(SDL_Event e) {
  if (eHandler)
    eHandler(e);
}

void Scene::update(void) {
  if (updater)
    updater();
}

void Scene::render(SDL_Renderer *ren) {
  if (renderer)
    renderer(ren);
}

// TODO: A cool title screen, maybe in a seperate file

void TitleScrenUpdater(void) {}

void TitleScreenRender(SDL_Renderer *) {}

Scene TitleScreen(nullptr, nullptr, nullptr);
