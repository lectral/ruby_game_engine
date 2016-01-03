#ifndef VISUAL_CPP
#define VISUAL_CPP  
#include <vector>
#include <SFML/Graphics.hpp>

struct Animation{
  std::string name;
  float duration;
  std::vector<sf::IntRect> rect;
};


class Visual
{
public:
   Visual(std::string name, sf::Texture & texture);
  ~ Visual();
  void SetName(std::string name);
  void SetSize(int x,int y);
  std::string GetName();
  void SetTexture(sf::Texture & texture);
  void AddAnimation(std::string name,float duration);
  sf::Texture & GetTexture();
  std::vector<sf::IntRect> GetAnimationRects(std::string name);
  std::vector<std::string> GetAnimationNames();
  std::vector<Animation>  GetAnimations();
  void AddAnimationFrame(std::string name,int x,int y,int h,int w);

private:
  std::string mName;
  int mSizeX;
  int mSizeY;
  sf::Texture & mTexture;
  std::vector<Animation> mAnimations;

};


#endif // VISUAL_CPP
  