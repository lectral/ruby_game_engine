#include "drawable.h"
#include "easylogging++.h"

Drawable::Drawable(unsigned int id, Visual & visual):
  mId(id)
{

    mHidden = false;
    mLayer = 1;
    mSprite.setTexture(visual.GetTexture(),true);
    for(int i = 0;i < visual.GetAnimations().size();i++){
      std::string name = visual.GetAnimations()[i].name;
      float duration =visual.GetAnimations()[i].duration;
      mAnimator.addAnimation(name,visual.GetAnimations()[i].frames,sf::seconds(duration));
     }
}

Drawable::~Drawable(){


}

unsigned int Drawable::GetID(){
  return mId;
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

void Drawable::SetHidden(bool state){
  mHidden = state;
}

bool Drawable::IsHidden(){
  return mHidden;
}

int const Drawable::GetLayer() const{
  return mLayer;
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

void Drawable::Update(sf::Time clock){
  mAnimator.update(clock);
  mAnimator.animate(mSprite);
  //mBoundingBox = mSprite.getGlobalBounds();
}

sf::Sprite & Drawable::GetSprite(){
  return mSprite;
}

void Drawable::UpdateFromPhysical(Physical * physical){
  //LOG(DEBUG) << "tracing: "<<physical->GetPosition().x;
  mSprite.setPosition(physical->GetPosition());
  mSprite.setRotation(physical->GetRotation());
  mSprite.setScale(physical->GetScale());
}

void Drawable::SetOwner(Entity * owner){
  mOwner = owner;
}


Entity * Drawable::GetOwner(){
  return mOwner;
}

