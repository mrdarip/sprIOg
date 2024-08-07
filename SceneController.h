#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "Scene.h"

class SceneController
{
private:
  Scene currentScene;
  Scene* scenes;

public:
  // Constructor
  SceneController(Scene initialScene);

  // Destructor
  ~SceneController();

  void changeScene(Scene newScene);
  void addScene(Scene newScene);
  void runCurrentScene();
};

#endif // SCENECONTROLLER_H