#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>
#include "visual.h"

class Entity;

class Drawable
{
public:
   Drawable(unsigned int id,Visual & visual);
  ~ Drawable();
  void UpdateFromPhysical(Physical * physical);


  unsigned int GetID();
  // Animations
  void PlayAnimation(std::string name);
  void StopAnimation();
  void SetRepeatAnimation(bool repeat);
  bool GetRepeatAnimation();
  
  //Sprite
  sf::Sprite & GetSprite();

  //Update
  void Update(sf::Time time);

  //Visibility
  bool IsHidden();
  void SetHidden(bool state);
  
  int const GetLayer() const;
  void SetLayer(unsigned int layer);

  void SetOwner(Entity * owner);
  Entity * GetOwner();

private:
  unsigned int mId;
  unsigned int mLayer;
  sf::Sprite mSprite;
  thor::Animator<sf::Sprite, std::string> mAnimator;
  bool mReady;
  bool mRepeatAnimation;
  bool mHidden;
  Entity * mOwner;
};



#endif // DRAWABLE_H
