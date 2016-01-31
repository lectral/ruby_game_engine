#ifndef VISUAL_H
#define VISUAL_H
#include <string>
#include "engine/physics/physical.h"
#include <SFML/Graphics.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>


struct Animation2{
  std::string name;
  float duration;
  thor::FrameAnimation frames;
};

class Visual
{
public:
   Visual(unsigned int id,std::string name,sf::Texture & texture);
  ~ Visual();
  void UpdateFromPhysical(Physical * physical);


  unsigned int GetID();
  std::string GetName();

  sf::Texture & GetTexture();

  //PreAnimations
  void AddAnimationFrame(std::string name,int x,int y,int h,int w);
  void AddAnimation(std::string name, float duration);
  
  std::vector<Animation2> & GetAnimations();

private:
  unsigned int mId;
  unsigned int mLayer;
  std::string mName;
  
  sf::Texture & mTexture;
  std::vector<Animation2> mAnimations;
};


#endif // VISUAL_H
