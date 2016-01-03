#include "physics_engine.h"
#include "easylogging++.h"

PhysicsEngine::PhysicsEngine(){
  mCount = 0;
}

PhysicsEngine::~PhysicsEngine(){

}

Physical * PhysicsEngine::GetPhysical(unsigned int id){
  for(auto physical = mPhysical.begin(); physical != mPhysical.end(); ++physical) {
    if(physical->GetId()==id){
      return &*physical;
    }
  }
}

unsigned int PhysicsEngine::AddPhysical(){
  mPhysical.push_back(Physical(mCount));
  mCount += 1;
  return mCount-1;
}