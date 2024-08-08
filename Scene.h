#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
  void (*fun)();
  int id;

public:
  Scene() : id(0), fun(nullptr) {}

  // Constructor
  Scene(int id, void (*fun)());
  
  void run();

  // Destructor
  ~Scene();
};

#endif // SCENE_H