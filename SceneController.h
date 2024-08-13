#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "Scene.h"

class SceneController
{
private:
  Scene currentScene;
  Scene* scenes; //this should be initialized to nullptr?
  int sceneCount;

public:
  // Constructor
  SceneController(Scene initialScene);

  // Destructor
  ~SceneController();

  void changeScene(Scene newScene);
  void changeScene(int sceneIndex);
  void addScene(Scene newScene);
  Scene getCurrentScene();
  void runCurrentScene();
};

#endif // SCENECONTROLLER_H