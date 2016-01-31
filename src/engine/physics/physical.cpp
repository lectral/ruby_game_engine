#include "physical.h"
#include "easylogging++.h"
#include "engine/entities/entity.h"

Physical::Physical(unsigned int id) :
mPosition(0,0)
{
  mId = id;
  mRotation = 0;
  mScale.x = 1;
  mScale.y = 1;
}

Physical::~Physical(){

}

unsigned int Physical::GetID(){
  return mId;
}


void Physical::SetPosition(float x, float y){
  mPosition.x = x;
  mPosition.y = y;
}

void Physical::SetPosition(sf::Vector2f & pos){
  mPosition = pos;
}

sf::Vector2f & Physical::GetPosition(){
  return mPosition;
}


void Physical::SetRotation(float angle){
  mRotation = angle;
}


float Physical::GetRotation(){
  return mRotation;
}

void Physical::SetScale(float x,float y){
  mScale.x = x;
  mScale.y = y;
}

const sf::Vector2f & Physical::GetScale(){
  return mScale;
}


void Physical::Move(float x,float y){
  mPosition.x += x;
  mPosition.y += y;
}

void Physical::Rotate(float angle){
  mRotation += angle;
}

void Physical::AddCollision(Physical * physical){
  mCollisions.push_back(physical);
}

bool Physical::CollidedWith(std::string name){
  for(auto it = mCollisions.begin();it != mCollisions.end();++it){
    if((*it)->GetOwner()->GetName() == name){
      return true;
    }
  }
  return false;
}

std::vector<Physical*> Physical::GetCollisions(){
  return mCollisions;
}

void Physical::SetOwner(Entity * owner){
  mOwner = owner;
}


Entity * Physical::GetOwner(){
  return mOwner;
}

void Physical::ClearCollisions(){
  mCollisions.clear();
}

void Physical::AddBoundingBox(BoundingBoxType type,sf::Vector2f props){
  BoundingBox bounding_box(type);
  bounding_box.SetProperties(props);
  bounding_box.SetOwner(this);
  mBoundingBoxes.push_back(bounding_box);
}

void Physical::AddBoundingBox(BoundingBoxType type,sf::Vector3f props){
  BoundingBox bounding_box(type);
  bounding_box.SetProperties(props);
  bounding_box.SetOwner(this);

  mBoundingBoxes.push_back(bounding_box);
}

void Physical::AddBoundingBox(BoundingBoxType type,sf::FloatRect props){
  BoundingBox bounding_box(type);
  bounding_box.SetProperties(props);
  bounding_box.SetOwner(this);
  mBoundingBoxes.push_back(bounding_box);

}
bool Physical::CheckCollisions(Physical & physical){
  for(auto first = mBoundingBoxes.begin();first != mBoundingBoxes.end(); ++first){
    for(auto second = physical.GetBoundingBoxes().begin(); second != physical.GetBoundingBoxes().end(); ++second){
     if(first->CheckCollision(*second)){
       return true;    
     }
   }
  }
  return false;
}

std::vector<BoundingBox> & Physical::GetBoundingBoxes(){
  return mBoundingBoxes;
}
void Physical::ClearBoundingBoxes(){
  mBoundingBoxes.clear();
}


void Physical::MapPositionToBoundingBoxes(){
  for(auto it = mBoundingBoxes.begin();it != mBoundingBoxes.end(); ++it){
    it->MapPosition(mPosition);
  }
}
