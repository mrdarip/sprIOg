#include "Scene.h"
#include "SceneController.h"

// Constructor
Scene::Scene(int id, void (*fun)())
{
  Serial.println("Creating scene: "+String(id));

  this->fun = fun;
  this->id = id;

  Serial.println("Scene created: "+String(this->id));
}

// Destructor
Scene::~Scene()
{
  Serial.print("Destroying scene: "+String(this->id));
  this->fun = nullptr;
  this->id = -1;
  Serial.println(" -> Destroyed successfully");
}

void Scene::run()
{
  Serial.println("Running scene: "+String(this->id));
  this->fun();
}

int Scene::getId()
{
  return this->id;
}

int Scene::getId() const {
  return this->id;
}
