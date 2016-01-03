#include "input_engine.h"

InputEngine::InputEngine(sf::RenderWindow &window) :
mWindow(window)
{
}

InputEngine::~InputEngine(){

}

int InputEngine::GetMouseX(){
  sf::Mouse::getPosition(mWindow).x;
}

int InputEngine::GetMouseY(){
  sf::Mouse::getPosition(mWindow).y;
}

void InputEngine::SetMouse(int x,int y){
  sf::Mouse::setPosition(sf::Vector2i(x,y));
}



bool InputEngine::IsKeyPressed(sf::Keyboard::Key key){
  for(int i=0;i<mPressedKeys.size();i++){
      if(mPressedKeys[i]==key){
        return true;
      }
  }
  return false;
}


void InputEngine::ProcessEvents(sf::Event & event){
  if(event.type == sf::Event::KeyPressed){
    mPressedKeys.push_back(event.key.code);
  }

  if(event.type == sf::Event::KeyReleased){
    for(int i=0;i<mPressedKeys.size();i++){
      if(mPressedKeys[i]==event.key.code){
        mPressedKeys.erase(mPressedKeys.begin()+i);
      }
    }
  }


}


