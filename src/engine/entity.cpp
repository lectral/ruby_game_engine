#include "entity.h"

Entity::Entity(unsigned int id,std::string name){
  mId = id;
  mName = name;
}

Entity::~Entity(){

}


unsigned int Entity::GetID(){
  return mId;
}


std::string Entity::GetName(){
  return mName;
}

void Entity::SetVisual(Visual * visual){
  mVisual = visual;
}


void Entity::SetPhysical(Physical * physical){
  mPhysical = physical;
}

Visual * Entity::GetVisual(){
  return mVisual;
}

Physical * Entity::GetPhysical(){
  return mPhysical;
}



