#ifndef PHYSICS_ENGINE_CPP
#define PHYSICS_ENGINE_CPP
#include <list>
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
  
};

#endif // PHYSICS_ENGINE_CPP

