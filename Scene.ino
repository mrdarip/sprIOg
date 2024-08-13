#include "Scene.h"

// Constructor
Scene::Scene(int id, void (*fun)())
{
  this->fun = fun;
  this->id = id;
}

// Destructor
Scene::~Scene()
{
  // Do nothing
}

void Scene::run()
{
  this->fun();
}

int Scene::getId()
{
  return this->id;
}
