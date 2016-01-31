#include "physics_engine.h"
#include "easylogging++.h"
#include "engine/entities/entity.h"


PhysicsEngine::PhysicsEngine() 
{
  mCount = 0;
}

PhysicsEngine::~PhysicsEngine(){

}

Physical * PhysicsEngine::GetPhysical(unsigned int id){
  for(auto physical = mPhysical.begin(); physical != mPhysical.end(); ++physical) {
    if(physical->GetID()==id){
      return &*physical;
    }
  }
}

unsigned int PhysicsEngine::AddPhysical(){
  mPhysical.push_back(Physical(mCount));
  mCount += 1;
  return mCount-1;
}


//[TO-DO] clean this mess up
void PhysicsEngine::Update(){
  mCollisions.clear();
  for(auto first = mPhysical.begin();first != mPhysical.end();++first){
    first->MapPositionToBoundingBoxes();
    for(auto second = mPhysical.begin();second != mPhysical.end();++second){
      second->MapPositionToBoundingBoxes();
      if(second->GetID() == first->GetID()) continue;
      if(second->CheckCollisions(*first)){
        first->AddCollision(&*second);
      } 
    }
  }
}


void PhysicsEngine::MapBoundingBoxes(){

}
