#include "visual.h"
#include "easylogging++.h"



Visual::Visual(std::string name, sf::Texture & texture):
  mName(name),
  mTexture(texture){

}

Visual::~Visual(){


}

void Visual::SetName(std::string name){
  mName = name;
}

void Visual::SetSize(int x,int y){
  mSizeX = x;
  mSizeY = y;
}

void Visual::SetTexture(sf::Texture & texture){
 mTexture = texture; 
}

std::string Visual::GetName(){
  return mName;
}

sf::Texture & Visual::GetTexture(){
  return mTexture;
}

void Visual::AddAnimation(std::string name,float duration = 1.0){
  Animation animation_stub;
  animation_stub.name = name;
  animation_stub.duration = duration;
  mAnimations.push_back(animation_stub);
  LOG(DEBUG) << "Animation " << name <<" for " << GetName() << " added";
}

std::vector<sf::IntRect> Visual::GetAnimationRects(std::string name){
  for(int i=0;i<mAnimations.size();i++){
    if(mAnimations[i].name==name){
      return mAnimations[i].rect;
    }
  }
}

std::vector<std::string> Visual::GetAnimationNames(){
  std::vector<std::string> names;
  for(int i;i<mAnimations.size();i++){
    names.push_back(mAnimations[i].name);
  }
  return names;
}

std::vector<Animation> Visual::GetAnimations(){
  return mAnimations;
}

void Visual::AddAnimationFrame(std::string name,int x,int y,int h,int w){
  for(int i;i<mAnimations.size();i++){
    if(mAnimations[i].name == name){
      mAnimations[i].rect.push_back(sf::IntRect(x,y,h,w));
    }
  }
  LOG(DEBUG) << "New frame added";
}

