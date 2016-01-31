#include "static.h"


Static::Static(unsigned int id,Visual & visual) : 
VisualObject(id)
{
  SetType(VISUAL_STATIC);
  mSprite.setTexture(visual.GetTexture(),true);
}

Static::~Static(){

}

void Static::Update(sf::Time time){

}

void Static::UpdateFromPhysical(Physical * physical){
  mSprite.setPosition(physical->GetPosition());
  mSprite.setRotation(physical->GetRotation());
  mSprite.setScale(physical->GetScale());
}


sf::Drawable * Static::GetDrawable(){
  return &mSprite;
}