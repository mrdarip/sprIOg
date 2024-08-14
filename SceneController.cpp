#include "SceneController.h"
#include "Scene.h"
#include <Arduino.h>

// Constructor
void SceneController::init(Scene initialScene)
{
  scenes = new Scene[1];
  scenes[0] = initialScene;
  sceneCount = 1;
  currentScene = initialScene;
}

void SceneController::changeScene(Scene newScene)
{
  Serial.println("Changing scene to: "+String(newScene.getId()));
  currentScene = newScene;
}

void SceneController::changeScene(int sceneIndex)
{
  Serial.println(sceneIndex);
  for(int i = 0; i < sceneCount; i++)
  {
    if(scenes[i].getId() == sceneIndex)
    {
      currentScene = scenes[i];
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
  return currentScene;
}

void SceneController::runCurrentScene()
{
  currentScene.run();
}