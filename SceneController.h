#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "Scene.h"

class SceneController
{
private:
  static Scene currentScene;
  static Scene* scenes;
  static int sceneCount;
public:
  static void changeScene(Scene newScene);
  static void changeScene(int sceneIndex);
  static void addScene(Scene newScene);
  static Scene getCurrentScene();
  static void runCurrentScene();
  static void removeScene(int sceneIndex);
  static void removeScene(Scene scene);
};

#endif // SCENECONTROLLER_H