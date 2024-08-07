#include "SceneController.h"

// Constructor
SceneController::SceneController(Scene initialScene)
{
  scenes = new Scene[1];
  scenes[0] = initialScene;
}

// Destructor
SceneController::~SceneController()
{
  delete[] scenes;
}

void SceneController::changeScene(Scene newScene)
{
  this->currentScene = newScene;
}

void SceneController::addScene(Scene newScene)
{
  Scene* temp = new Scene[sceneCount + 1];
  for (int i = 0; i < sceneCount; i++)
  {
      temp[i] = scenes[i];
  }
  temp[sceneCount] = newScene;
  delete[] scenes;
  scenes = temp;
  sceneCount++;
}

void SceneController::runCurrentScene()
{
  this->currentScene.run();
}