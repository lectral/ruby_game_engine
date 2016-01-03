#ifndef PHYSICAL_H
#define PHYSICAL_H
#include <SFML/Graphics.hpp>

class Physical
{
public:
  Physical(unsigned int id);
  ~Physical();
  
  void SetPosition(float x,float y);
  void SetPosition(sf::Vector2f & pos);
  
  void SetRotation(float angle);
  float GetRotation();

  void SetScale(float x,float y);
  const sf::Vector2f & GetScale();
  
  void Move(float x,float y);
  void Rotate(float angle);

  const sf::Vector2f & GetPosition();

  unsigned int GetId();


private:

  unsigned int mId;
  sf::Vector2f mPosition;
  sf::Vector2f mScale;
  float mRotation;

  
};


#endif // PHYSICAL_H
