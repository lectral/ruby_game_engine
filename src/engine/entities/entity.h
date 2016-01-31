#ifndef ENTITY_H
#define ENITY_H
//#include "visual.h"
#include "engine/graphics/animated.h"
#include "engine/physics/physical.h"
#include "engine/mruby/scripted.h"
#include "engine/graphics/text.h"

class Entity
{
public:
   Entity(unsigned int id,std::string name);
  ~ Entity();
  Animated * GetVisual();
  Physical * GetPhysical();
  Scripted * GetScripted();
  Text     * GetTexted();
  void SetVisual(Animated * visual);
  void SetPhysical(Physical * physical);
  void SetScripted(Scripted * scripted);
  void SetTexted(Text * texted);
  //
  unsigned int GetID();
  std::string GetName();

  // physics
  void Update();

  // compare operator
  bool operator==(unsigned int other);
private:
  std::string mName;
  unsigned int mId;
  Animated * mVisual;
  Physical * mPhysical;
  Scripted * mScript;
  Text * mText;
};


#endif // ENITY_H
