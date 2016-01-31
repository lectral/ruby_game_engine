#include "bounding_box.h"
#include "physical.h"
#include <math.h>
#include "easylogging++.h"

BoundingBox::BoundingBox(BoundingBoxType type) {
  mType = type;
}

BoundingBox::~BoundingBox(){
  
}

BoundingBoxType BoundingBox::GetType(){
  return mType;
}

sf::Vector3f & BoundingBox::GetCircle(){
  return mCircle;
}

sf::Vector2f & BoundingBox::GetPoint(){
  return mPoint;
}

sf::FloatRect & BoundingBox::GetRect(){
  return mRect;
}


void BoundingBox::SetProperties(sf::Vector3f circle){
  mCircle = circle;
}

void BoundingBox::SetProperties(sf::Vector2f point){
  mPoint = point;
}

void BoundingBox::SetProperties(sf::FloatRect rect){
  mRect = rect;
}

bool BoundingBox::ThisCollidesPoint(sf::Vector2f & b){
  switch ( mType )
      {
         case RECT:
           //LOG(DEBUG) << "mRect: left "<<mRect.left<<" x "<<mRect.top << " "<<mRect.width<<" "<<mRect.height;
           //LOG(DEBUG) << "b: left "<<b.x<<" x "<<b.y;
            return mRect.contains(b);
            break;
         case POINT:
            return mPoint == b;
            break;
         case CIRCLE:
            // (x - center_x)^2 + (y - centerdxedxe_y)^2 < radius^2
            float a1 = sqrt(pow(b.x - mCircle.x,2) + pow(b.y - mCircle.y,2));
            float a2 = mCircle.z;
            //LOG(DEBUG) << "a1: "<<a1<<" a2: "<<a2;
            return a1 < a2 ;
            break;
      }
}

bool BoundingBox::ThisCollidesCircle(sf::Vector3f & b){
  switch ( mType )
      {
         case RECT:
            return false;
            break;
         case POINT:{
              float a1 = sqrt(pow(mPoint.x - b.x,2) + pow(mPoint.y - b.y,2));
              float a2 = b.z;
             // LOG(DEBUG) << "a1: "<<a1<<" a2: "<<a2;
              return a1 < a2 ;
              break;
            }
         case CIRCLE:
            return (Distance(mCircle.x,mCircle.y,b.x,b.y)) < (mCircle.z + b.z);
            break;
      }
}

bool BoundingBox::ThisCollidesRect(sf::FloatRect & b){
  switch ( mType )
    {
       case RECT:
          mRect.intersects(b);
          break;
       case POINT:
          //LOG(DEBUG) << "b: left "<<b.left<<" x "<<b.top;
          b.contains(mPoint);
          break;
       case CIRCLE:
          return false;
          break;
    }
}

sf::Vector2f BoundingBox::GetMappedPosition(){
  sf::Vector2f tmp = GetOwner()->GetPosition();
  switch ( mType )
      {
         case RECT:
            tmp.x += mRect.left;
            tmp.y += mRect.top;
            return tmp;
            break;
         case POINT:
            tmp.x += mPoint.x;
            tmp.y += mPoint.y;
            return tmp;
            break;
         case CIRCLE:
            tmp.x += mCircle.x;
            tmp.y += mCircle.y;
            return tmp;
            break;
      }
} 


float BoundingBox::Distance(BoundingBox & bbox){
  sf::Vector2f a = GetMappedPosition();
  sf::Vector2f b = bbox.GetMappedPosition();
  return sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
}

float BoundingBox::Distance(float x1,float y1, float x2, float y2){
  sf::Vector2f a(x1,y1);
  sf::Vector2f b(x2,y2);
  return sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
}



void BoundingBox::SetOwner(Physical * owner){
  mOwner = owner;
}


Physical * BoundingBox::GetOwner(){
  return mOwner;
}

bool BoundingBox::CheckCollision(BoundingBox & a){
  switch(a.GetType()){
    case POINT:
   // LOG(DEBUG) << "colldies point";
      return ThisCollidesPoint(a.GetPoint());
    break;
    case CIRCLE:
      return ThisCollidesCircle(a.GetCircle());
    break;
    case RECT:
      return ThisCollidesRect(a.GetRect());
    break;
  }
}

void BoundingBox::MapPosition(sf::Vector2f new_position){
  switch(mType){
    case POINT:
      mPoint = new_position;
    break;
    case CIRCLE:
      mCircle.x = new_position.x;
      mCircle.y = new_position.y;
    break;
    case RECT:
      mRect.left = new_position.x;
      mRect.top = new_position.y;
    break;
  }
}
