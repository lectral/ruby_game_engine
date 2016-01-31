#include "entity.h"

Entity::Entity(unsigned int id,std::string name){
  mId = id;
  mName = name;
  mVisual = NULL;
  mText = NULL;
}

Entity::~Entity(){

}


unsigned int Entity::GetID(){
  return mId;
}


std::string Entity::GetName(){
  return mName;
}

void Entity::SetVisual(Animated * visual){
  visual->SetOwner(this);
  mVisual = visual;
}


void Entity::SetPhysical(Physical * physical){
  physical->SetOwner(this);
  mPhysical = physical;
}

void Entity::SetScripted(Scripted * scripted){
  scripted->SetOwner(this);
  mScript = scripted;
}

void Entity::SetTexted(Text * text) {
  mText = text; 
}

Animated * Entity::GetVisual(){
  return mVisual;
}

Physical * Entity::GetPhysical(){
  return mPhysical;
}


Scripted * Entity::GetScripted(){
  return mScript;
}

Text * Entity::GetTexted() {
  return mText; 
}

bool Entity::operator==(unsigned int other){
  return this->GetID() == other;
}


