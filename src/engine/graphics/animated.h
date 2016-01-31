#ifndef ANIMATED_H
#define ANIMATED_H
#include "visual_object.h"

class Animated : public VisualObject {
public:
  Animated(unsigned int id,Visual & visual);
  ~Animated();
  
  void PlayAnimation(std::string name);
  void StopAnimation();
  void SetRepeatAnimation(bool repeat);
  bool GetRepeatAnimation();
  void UpdateFromPhysical(Physical * physical);
  sf::Vector2f GetCoords();
  void UpdateCoords(sf::Vector2f & coords);
  void Update(sf::Time time);
  sf::Drawable * GetDrawable();
  sf::Sprite & GetSprite();

private:
  thor::Animator<sf::Sprite, std::string> mAnimator;
  bool mRepeatAnimation;
  sf::Sprite mSprite;
  double mFrameTime;
};


#endif // ANIMATED_H
