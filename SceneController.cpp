#include "SceneController.h"
#include "Scene.h"
#include <Arduino.h>

Scene SceneController::currentScene;
Scene* SceneController::scenes = nullptr;
int SceneController::sceneCount = 0;

// Constructor
void SceneController::init(Scene initialScene)
{
  Serial.println("Initializing scene controller");
  sceneCount = 1;
  scenes = new Scene[1];
  scenes[0] = initialScene;
  currentScene = initialScene;
  Serial.println("Scene controller initialized");
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

  Serial.println("Scene added: "+String(newScene.getId()));
}

Scene SceneController::getCurrentScene()
{
  return currentScene;
}

void SceneController::runCurrentScene()
{
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

SceneController.init(Scene(0, []() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("Default Scene");
}));