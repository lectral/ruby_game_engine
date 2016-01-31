#include "visual.h"
#include "easylogging++.h"

Visual::Visual(unsigned int id,std::string name,sf::Texture & texture):
  mId(id),
  mName(name),
  mTexture(texture)
{
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


std::vector<Animation2> & Visual::GetAnimations(){
  return mAnimations;
}

sf::Texture & Visual::GetTexture(){
  return mTexture;
}


