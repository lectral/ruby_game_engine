#ifndef PHYSICAL_H
#define PHYSICAL_H
#include <SFML/Graphics.hpp>
#include "engine/physics/bounding_box.h"


class Entity;

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

  sf::Vector2f & GetPosition();

  unsigned int GetID();

  void AddCollision(Physical * physical);
  void ClearCollisions();

  bool CollidedWith(std::string name);

  std::vector<Physical*> GetCollisions();

  //[TO-DO] Move this to parent class
  Entity * GetOwner();
  void SetOwner(Entity * entity);
  

  void AddBoundingBox(BoundingBoxType type,sf::Vector2f props);
  void AddBoundingBox(BoundingBoxType type,sf::Vector3f props);
  void AddBoundingBox(BoundingBoxType type,sf::FloatRect props);
  std::vector<BoundingBox> & GetBoundingBoxes();
  bool CheckCollisions(Physical & physical);
  void ClearBoundingBoxes();

  void Update();
  void MapPositionToBoundingBoxes();
private:

  unsigned int mId;
  sf::Vector2f mPosition;
  sf::Vector2f mScale;
  float mRotation;
  std::vector<Physical*> mCollisions;
  std::vector<BoundingBox> mBoundingBoxes;
  sf::FloatRect mBoundingBox;

  Entity * mOwner;


  
};


#endif // PHYSICAL_H
