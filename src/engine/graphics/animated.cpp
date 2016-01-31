#include "animated.h"
#include "easylogging++.h"


Animated::Animated(unsigned int id,Visual & visual) : 
VisualObject(id)
{
  SetType(VISUAL_ANIMATED);
  mSprite.setTexture(visual.GetTexture(),true);
  for(int i = 0;i < visual.GetAnimations().size();i++){
    std::string name = visual.GetAnimations()[i].name;
    float duration =visual.GetAnimations()[i].duration;
    mAnimator.addAnimation(name,visual.GetAnimations()[i].frames,sf::seconds(duration));
   }
}

Animated::~Animated(){

}

void Animated::PlayAnimation(std::string name){
  mAnimator.playAnimation(name,mRepeatAnimation);
}

void Animated::StopAnimation(){
  mAnimator.stopAnimation();
}

void Animated::SetRepeatAnimation(bool repeat){
  mRepeatAnimation = repeat;
  if(mAnimator.isPlayingAnimation()){
    mAnimator.playAnimation(mAnimator.getPlayingAnimation(),mRepeatAnimation);
  }
}

bool Animated::GetRepeatAnimation(){
  return mRepeatAnimation;
}

void Animated::Update(sf::Time time){
  mAnimator.update(time);
  mAnimator.animate(mSprite);
}


void Animated::UpdateFromPhysical(Physical * physical){
  //LOG(DEBUG) << "tracing: "<<physical->GetPosition().x;
  mSprite.setPosition(physical->GetPosition());
  mSprite.setRotation(physical->GetRotation());
  mSprite.setScale(physical->GetScale());
}

sf::Drawable * Animated::GetDrawable(){
  return &mSprite;
}

sf::Sprite & Animated::GetSprite(){
  return mSprite;
}

sf::Vector2f Animated::GetCoords(){
  return mSprite.getPosition();
}

void Animated::UpdateCoords(sf::Vector2f & coords){
  mSprite.move(coords);
}