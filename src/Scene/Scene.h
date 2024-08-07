#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
  auto loop();
  int id;

public:
  // Constructor
  Scene(int id, auto loop);

  // Destructor
  ~Scene();
};

#endif // SCENE_H