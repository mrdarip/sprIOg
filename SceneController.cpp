#include "SceneController.h"
#include <vector>

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
  this->scenes.push_back(newScene);
}

void SceneController::runCurrentScene()
{
  this->currentScene.;
}