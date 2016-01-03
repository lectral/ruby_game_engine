#include "visual.h"


Visual::Visual(unsigned int id,std::string name,sf::Texture & texture):
  mId(id),
  mName(name),
  mTexture(texture)
{
    mReady = false;
    mHidden = false;
    mLayer = 1;
}

Visual::~Visual(){


}

unsigned int Visual::GetID(){
  return mId;
}

std::string Visual::GetName(){
  return mName;
}

void Visual::CreateThis(){
  
  if(mReady) return; // Break if already exists

  mSprite.setTexture(mTexture,true);
  for(int i=0;i<mAnimations.size();i++){
    std::string name = mAnimations[i].name;
    float duration = mAnimations[i].duration;
      mAnimator.addAnimation(name,mAnimations[i].frames,sf::seconds(duration));
   }
  mReady = true;
}

void Visual::AddAnimation(std::string name, float duration){
  Animation2 new_animation;
  new_animation.name = name;
  new_animation.duration = duration;
  mAnimations.push_back(new_animation);
}


void Visual::AddAnimationFrame(std::string name,int x,int y,int h,int w){
  sf::IntRect rect(x,y,h,w);
  for(int i=0;i<mAnimations.size();i++){
    if(mAnimations[i].name==name){
      mAnimations[i].frames.addFrame(1.f,rect);
      return;
    }
  }
}

void Visual::PlayAnimation(std::string name){
  mAnimator.playAnimation(name,mRepeatAnimation);
}

void Visual::StopAnimation(){
  mAnimator.stopAnimation();
}

void Visual::SetRepeatAnimation(bool repeat){
  mRepeatAnimation = repeat;
  if(mAnimator.isPlayingAnimation()){
    mAnimator.playAnimation(mAnimator.getPlayingAnimation(),mRepeatAnimation);
  }
}

bool Visual::GetRepeatAnimation(){
  return mRepeatAnimation;
}

void Visual::SetHidden(bool state){
  mHidden = state;
}

bool Visual::IsHidden(){
  return mHidden;
}

int const Visual::GetLayer() const{
  return mLayer;
}

void Visual::SetLayer(unsigned int layer){
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

void Visual::Update(sf::Time clock){
  mAnimator.update(clock);
  mAnimator.animate(mSprite);
  //mBoundingBox = mSprite.getGlobalBounds();
}

sf::Sprite & Visual::GetSprite(){
  return mSprite;
}

void Visual::UpdateFromPhysical(Physical * physical){
  mSprite.setPosition(physical->GetPosition());
  mSprite.setRotation(physical->GetRotation());
  mSprite.setScale(physical->GetScale());
}

