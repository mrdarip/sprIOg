#include "Scene.h"

// Constructor
Scene::Scene(int id, void (*loop)())
{
  this->loop = loop;
  this->id = id;
}

// Destructor
Scene::~Scene()
{
  // Do nothing
}

void Scene::run()
{
    
    this->loop();
 Serial.print("runniiinng");
}