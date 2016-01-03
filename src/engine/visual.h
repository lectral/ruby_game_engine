#ifndef VISUAL_H
#define VISUAL_H
#include <string>
#include "physical.h"
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
  // Animations
  void PlayAnimation(std::string name);
  void StopAnimation();
  void SetRepeatAnimation(bool repeat);
  bool GetRepeatAnimation();

  //PreAnimations
  void AddAnimationFrame(std::string name,int x,int y,int h,int w);
  void AddAnimation(std::string name, float duration);
  
  //Sprite
  sf::Sprite & GetSprite();

  //Update
  void Update(sf::Time time);

  //Visibility
  bool IsHidden();
  void SetHidden(bool state);
  
  int const GetLayer() const;
  void SetLayer(unsigned int layer);

  // Load
  void CreateThis();

private:
  unsigned int mId;
  unsigned int mLayer;
  std::string mName;
  
  sf::Texture & mTexture;
  sf::Sprite mSprite;
  std::vector<Animation2> mAnimations;
  thor::Animator<sf::Sprite, std::string> mAnimator;
  bool mReady;
  bool mRepeatAnimation;
  bool mHidden;

};


#endif // VISUAL_H
