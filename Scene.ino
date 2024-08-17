#include "Scene.h"
#include "SceneController.h"

// Constructor
Scene::Scene(int id, void (*fun)())
{
  Serial.println("Creating scene: "+String(id));

  this->fun = fun;
  this->id = id;

  SceneController::addScene(*this);
}

// Destructor
Scene::~Scene()
{
  SceneController::removeScene(this->id);
  Serial.println("Deleting scene: "+String(this->id));
}

void Scene::run()
{
  this->fun();
}

int Scene::getId()
{
  return this->id;
}
