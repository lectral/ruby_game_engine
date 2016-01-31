#ifndef STATIC_VISUAL_H
#define STATIC_VISUAL_H
#include "visual_object.h"

class Static : VisualObject {
public:
  Static(unsigned int id,Visual & visual);
  ~Static();
  sf::Drawable * GetDrawable();
  void Update(sf::Time time);
  void UpdateFromPhysical(Physical * physical);
private:
  sf::Sprite mSprite;
};


#endif // STATIC_VISUAL_H
