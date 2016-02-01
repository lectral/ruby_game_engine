#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include "visual_object.h"
class Text : public VisualObject
{
public:
  Text(unsigned int id);
  virtual ~Text();
  void SetFont(sf::Font & font);
  void SetText(std::string text);
  void AddText(std::string text);
  void SetSize(unsigned int size);
  void SetColor(int r,int g,int b);
  void Update();
  void UpdateCoords(sf::Vector2f & coords);
  void UpdateFromPhysical(Physical * physical);
  std::string GetText();
  sf::Text * GetDrawable();
private:
  sf::Text mText;
};

#endif /* end of include guard: TEXT_H */
