#include "Scene.h"

// Constructor
Scene::Scene(int id, auto loop)
{
  this->loop = loop;
  this->id = id;
}

// Destructor
Scene::~Scene()
{
  // Do nothing
}