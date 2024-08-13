#include "SceneController.h"
#include "Scene.h"
#include <Arduino.h>

// Constructor
SceneController::SceneController(Scene initialScene)
{
  this->scenes = new Scene[1];
  this->scenes[0] = initialScene;
  this->sceneCount = 1;
  this->currentScene = initialScene;
}

// Destructor
SceneController::~SceneController()
{
  delete[] scenes;
}

void SceneController::changeScene(Scene newScene)
{
  Serial.println("Changing scene to: "+String(newScene.getId()));
  this->currentScene = newScene;
}

void SceneController::changeScene(int sceneIndex)
{
  Serial.println(sceneIndex);
  for(int i = 0; i < sceneCount; i++)
  {
    if(scenes[i].getId() == sceneIndex)
    {
      this->currentScene = scenes[i];
      return;
    }
  }
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

Scene SceneController::getCurrentScene()
{
  return this->currentScene;
}

void SceneController::runCurrentScene()
{
  this->currentScene.run();
}