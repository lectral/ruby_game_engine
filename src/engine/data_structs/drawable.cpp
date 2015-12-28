#include "drawable.h"
#include "easylogging++.h"
#include <SFML/System/Time.hpp>

Drawable::Drawable(int id,std::string str_id,Visual & visual,int layer) :
mID(id),
mStringID(str_id),
mVisual(visual),
mLayer(layer)
{
  mSprite.setTexture(mVisual.GetTexture());
  std::vector<Animation> animations = mVisual.GetAnimations();
  for(int i=0;i<animations.size();i++){
    std::string name = animations[i].name;
    std::vector<sf::IntRect> rects = animations[i].rect;
    thor::FrameAnimation anim;
    float duration = 1.0/rects.size();
    for(int j=0;j<rects.size();j++){
      anim.addFrame(1.f,rects[j]);
    }
    mAnimator.addAnimation(name,anim,sf::seconds(animations[i].duration));

  }
  //mAnimator.playAnimation("run");
  mRepeatAnimation = false;
  LOG(DEBUG) << "Drawable created ["<<mStringID<<"]["<<mID<<"]";
 
}



Drawable::~Drawable(){

}

void Drawable::SetPosition(float x, float y){
  mSprite.setPosition(x,y);
}

void Drawable::SetRotation(float angle){
  mSprite.setRotation(angle);
}

void Drawable::PlayAnimation(std::string name){
  mAnimator.playAnimation(name,mRepeatAnimation);
}

void Drawable::StopAnimation(){
  mAnimator.stopAnimation();
}

void Drawable::SetRepeatAnimation(bool repeat){
  mRepeatAnimation = repeat;
  if(mAnimator.isPlayingAnimation()){
    mAnimator.playAnimation(mAnimator.getPlayingAnimation(),mRepeatAnimation);
  }
}

bool Drawable::GetRepeatAnimation(){
  return mRepeatAnimation;
}

void Drawable::SetLayer(unsigned int layer){
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


void Drawable::SetScale(float x,float y){
  mSprite.setScale(x,y);
}

int const Drawable::GetLayer() const{
  return mLayer;
}


void Drawable::Move(float x,float y){
  mSprite.move(x,y);
}

void Drawable::Rotate(float angle){
  mSprite.rotate(angle);
}



float Drawable::GetPositionX(){
  return mSprite.getPosition().x;
}


float Drawable::GetPositionY(){
  return mSprite.getPosition().y;
}

void Drawable::Update(sf::Time clock){
  mAnimator.update(clock);
  mAnimator.animate(mSprite);
}

sf::Sprite & Drawable::GetSprite(){
  return mSprite;
}


int Drawable::GetID(){
  return mID;
}

std::string Drawable::GetStringID(){
  return mStringID;
}


void Drawable::SetHidden(bool state){
  mHidden = state;
}

bool Drawable::IsHidden(){
  return mHidden;
}
