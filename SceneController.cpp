#include "SceneController.h"

// Constructor
SceneController::SceneController(Scene initialScene)
{
  this->currentScene = initialScene;
}

// Destructor
SceneController::~SceneController()
{
  // Do nothing
}

void SceneController::changeScene(Scene newScene)
{
  this->currentScene = newScene;
}

void SceneController::addScene(Scene newScene)
{
  Scene* temp = this->scenes;
  this->scenes = new Scene[this->scenes.length + 1];
  for (int i = 0; i < this->scenes.length; i++)
  {
    this->scenes[i] = temp[i];
  }
}

void SceneController::runCurrentScene()
{
  this->currentScene.;
}