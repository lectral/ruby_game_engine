#include "visual_object.h"

VisualObject::VisualObject(unsigned int id){
  SetID(id);
  mHidden = false;
  mLayer = 1;
}

VisualObject::~VisualObject(){

}


int const VisualObject::GetLayer() const{
  return mLayer;
}

sf::Drawable * VisualObject::GetDrawable(){

}

void VisualObject::SetType(int type){
  mType = type;
}

int VisualObject::GetType(){
  return mType;
}


unsigned int VisualObject::GetID(){
  return mId;
}

void VisualObject::SetID(unsigned int id){
  mId = id;
}


void VisualObject::SetLayer(unsigned int layer){
  if(layer<0){
    mLayer = 0;
  }
  else if(layer>99){
    mLayer = 99;
  }
  else{
    mLayer = layer;
  }

}

void VisualObject::SetOwner(Entity * owner){
  mOwner = owner;
}


void VisualObject::SetHidden(bool state){
  mHidden = state;
}

bool VisualObject::IsHidden(){
  return mHidden;
}

void VisualObject::Update(sf::Time time){
}
 

void VisualObject::UpdateFromPhysical(Physical * physical){
}
