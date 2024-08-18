#include "SceneController.h"
#include "Scene.h"
#include <Arduino.h>

Scene SceneController::currentScene;
Scene* SceneController::scenes = nullptr;
int SceneController::sceneCount = 0;

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
  Serial.println("Adding scene: "+String(newScene.getId()));

  Scene* temp = new Scene[sceneCount + 1];
  for (int i = 0; i < sceneCount; i++)
  {
      temp[i] = scenes[i];
  }
  temp[sceneCount] = newScene;
  delete[] scenes;
  scenes = temp;
  sceneCount++;

  if(currentScene.getId() == -1)
  {
    currentScene = newScene;
  }
  
  Serial.println("Scene added: "+String(newScene.getId()));
}

Scene SceneController::getCurrentScene()
{
  return currentScene;
}

void SceneController::runCurrentScene()
{
  Serial.println("Running current scene: "+String(currentScene.getId()));
  currentScene.run();
}

void SceneController::removeScene(int sceneIndex)
{
  Scene* temp = new Scene[sceneCount - 1];
  int j = 0;
  for (int i = 0; i < sceneCount; i++)
  {
    if(scenes[i].getId() != sceneIndex)
    {
      temp[j] = scenes[i];
      j++;
    }
  }
  delete[] scenes;
  scenes = temp;
  sceneCount--;
}

void SceneController::removeScene(Scene scene)
{
  removeScene(scene.getId());
}