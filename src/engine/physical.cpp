#include "physical.h"
#include "easylogging++.h"
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

unsigned int Physical::GetId(){
  return mId;
}


void Physical::SetPosition(float x, float y){
  mPosition.x = x;
  mPosition.y = y;
}

void Physical::SetPosition(sf::Vector2f & pos){
  mPosition = pos;
}

const sf::Vector2f & Physical::GetPosition(){
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
