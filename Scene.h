#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
  void (*fun)();
  int id;

public:
  // Constructor
  Scene(int id, void (*fun)());
  Scene() : id(-1), fun(nullptr) {} //This should be defined in the .cpp file to avoid potential issues with inline initialization.?

  void run();
  int getId();

  // Destructor
  ~Scene();
};

#endif // SCENE_H