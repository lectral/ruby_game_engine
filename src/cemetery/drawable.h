#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "visual.h"
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>

class Drawable
{
public:
  Drawable(int id,std::string str_id,Visual & visual,int layer);
  ~Drawable();
  void SetPosition(float x,float y);
  void SetRotation(float angle);
  void SetScale(float x,float y);
  void Move(float x,float y);
  void Rotate(float angle);
  float GetPositionX();
  float GetPositionY();
  void PlayAnimation(std::string name);
  void StopAnimation();
  void SetRepeatAnimation(bool repeat);
  bool GetRepeatAnimation();
  sf::Sprite & GetSprite();
  bool IsHidden();
  void SetHidden(bool state);
  int GetID();
  std::string GetStringID();
  int const GetLayer() const;
  void SetLayer(unsigned int layer);
  void Update(sf::Time clock);
  bool ContainsPoint(float x,float y);

private:
  int mID;
  int mLayer;
  int mCurrentFrame;
  int mFrames;
  int mSizeX;
  int mSizeY;
  float mSpeed;
  bool mRepeatAnimation;
  bool mHidden;
  std::string mStringID;
  //sf::Texture & mTexture;
  sf::Sprite mSprite;
  Visual & mVisual;
  thor::Animator<sf::Sprite, std::string> mAnimator;
  sf::FloatRect mBoundingBox;
};


#endif // DRAWABLE_H
