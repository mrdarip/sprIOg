#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
  void (*loop)();
  int id;

public:
  // Constructor
  Scene(int id, void (*loop)());
  
  void run();

  // Destructor
  ~Scene();
};

#endif // SCENE_H