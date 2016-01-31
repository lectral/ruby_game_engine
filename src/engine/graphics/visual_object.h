#ifndef VISUAL_OBJECT_H
#define VISUAL_OBJECT_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include "visual.h"


enum VisualType { VISUAL_STATIC, VISUAL_ANIMATED };

class VisualObject
{
public:
  VisualObject(unsigned int id);
  ~VisualObject();

  bool IsHidden();
  void SetHidden(bool state);

  void SetType(int type);
  int GetType();

  unsigned int GetID();
  void SetID(unsigned int);

  sf::Drawable * GetDrawable();

  int const GetLayer() const;
  void SetLayer(unsigned int layer);

  void SetOwner(Entity * owner);
  Entity * GetOwner();


  virtual void Update(sf::Time time);
  virtual void UpdateFromPhysical(Physical * physical);

private:
  unsigned int mId;
  sf::Drawable * mDrawable;
  Entity * mOwner;
  bool mHidden;
  unsigned int mLayer;
  int mType;
};


#endif // VISUAL_OBJECT_H
