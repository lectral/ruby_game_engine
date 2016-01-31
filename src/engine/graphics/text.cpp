#include "text.h"

Text::Text(unsigned int id):
VisualObject(id),
mText()
{
  mText.setColor(sf::Color::Red);
}

Text::~Text(){


}

void Text::SetFont(sf::Font & font) {
  mText.setFont(font);
  mText.setCharacterSize(100);
}

void Text::SetText(std::string text) {
  mText.setString(text);
}

void Text::AddText(std::string text) {
  mText.setString(mText.getString()+text);
}

void Text::Update() {
  
}



std::string Text::GetText() {
  return mText.getString();
}

sf::Text * Text::GetDrawable() {
  return &mText;
}

void Text::UpdateCoords(sf::Vector2f & coords){
  mText.move(coords);
}

void Text::UpdateFromPhysical(Physical * physical) {
 mText.setPosition(physical->GetPosition()); 
 mText.setRotation(physical->GetRotation());
 mText.setScale(physical->GetScale());
}









