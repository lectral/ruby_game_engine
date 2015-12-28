#include "input_engine.h"

InputEngine::InputEngine(){


}

InputEngine::~InputEngine(){

}

int InputEngine::GetMouseX(){
  sf::Mouse::getPosition().x;
}

int InputEngine::GetMouseY(){
  sf::Mouse::getPosition().y;
}

void InputEngine::SetMouse(int x,int y){
  sf::Mouse::setPosition(sf::Vector2i(x,y));
}


bool InputEngine::IsKeyPressed(sf::Keyboard::Key key){
  return sf::Keyboard::isKeyPressed(key);
}
// InputEngine::GetMouseV(){
// }