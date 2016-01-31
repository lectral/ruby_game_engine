#ifndef PHYSICS_ENGINE_CPP
#define PHYSICS_ENGINE_CPP
#include <list>
#include <map>

#include "physical.h"


class PhysicsEngine
{
public:
  PhysicsEngine();
  ~PhysicsEngine();
  Physical * GetPhysical(unsigned int id);
  unsigned int AddPhysical();
  void Update();
private:
  unsigned int mCount;
  std::list<Physical> mPhysical;
  std::vector<Physical*> mCollisions;

  void MapBoundingBoxes();

  //Box2d props
 // b2Vec2 mGravity;
 // b2World mWorld;
  
};

#endif // PHYSICS_ENGINE_CPP

