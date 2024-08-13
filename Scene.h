#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
  void (*fun)();
  int id;

public:
  Scene() : id(0), fun(nullptr) {} //This should be defined in the .cpp file to avoid potential issues with inline initialization.?

  // Constructor
  Scene(int id, void (*fun)());
  
  void run();
  int getId();
  // Destructor
  ~Scene();
};

#endif // SCENE_H