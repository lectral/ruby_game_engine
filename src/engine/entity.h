#ifndef ENTITY_H
#define ENITY_H
#include "visual.h"
#include "physical.h"

class Entity
{
public:
   Entity(unsigned int id,std::string name);
  ~ Entity();
  Visual * GetVisual();
  Physical * GetPhysical();

  void SetVisual(Visual * visual);
  void SetPhysical(Physical * physical);

  //
  unsigned int GetID();
  std::string GetName();

  // physics
  void Update();
private:
  std::string mName;
  unsigned int mId;
  Visual * mVisual;
  Physical * mPhysical;
};


#endif // ENITY_H
