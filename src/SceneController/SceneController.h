#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "Scene.h"
#include <vector>

class SceneController
{
private:
  Scene currentScene;
  Vector<Scene> scenes;

public:
  // Constructor
  SceneController(Scene initialScene);

  // Destructor
  ~SceneController();

  void changeScene(Scene newScene);
  void addScene(Scene newScene);
};

#endif // SCENECONTROLLER_H