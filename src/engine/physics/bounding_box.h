#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
#include <SFML/Graphics.hpp>

class Physical;
enum BoundingBoxType {
  RECT,
  CIRCLE,
  POINT
};

class BoundingBox{
public:
  BoundingBox(BoundingBoxType type);
  ~BoundingBox();
  void SetProperties(sf::Vector3f circle);
  void SetProperties(sf::Vector2f point);
  void SetProperties(sf::FloatRect rect);
  bool CheckCollision(BoundingBox & a);

  void MapPosition(sf::Vector2f new_position);

  BoundingBoxType GetType();

  sf::Vector3f & GetCircle();
  sf::Vector2f & GetPoint();
  sf::FloatRect & GetRect();
  void SetOwner(Physical * physical);
  Physical * GetOwner();

private:
  BoundingBoxType mType;
  sf::Vector3f mCircle;
  sf::Vector2f mPoint;
  sf::FloatRect mRect;
  Physical * mOwner;

  sf::Vector2f GetMappedPosition();

  bool ThisCollidesPoint(sf::Vector2f & b);
  bool ThisCollidesCircle(sf::Vector3f & b);
  bool ThisCollidesRect(sf::FloatRect & b);

  float Distance(BoundingBox & bbox);
  float Distance(float x1,float y1, float x2, float y2);

};


#endif // BOUNDING_BOX_H
