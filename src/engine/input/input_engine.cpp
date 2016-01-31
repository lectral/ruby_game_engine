#include "input_engine.h"
#include "easylogging++.h"

InputEngine::InputEngine(sf::RenderWindow &window) :
mWindow(window)
{
}

InputEngine::~InputEngine(){

}

int InputEngine::GetMouseX(){
  return mMousePosition.x;
}

int InputEngine::GetMouseY(){ 
  return mMousePosition.y;
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

bool InputEngine::IsMousePressed(sf::Mouse::Button button){
  for(int i=0;i<mPressedMouseButtons.size();i++){
      if(mPressedMouseButtons[i]==button){
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
    mPressedKeys.erase(std::remove(mPressedKeys.begin(), mPressedKeys.end(), event.key.code), mPressedKeys.end());

  }
  
  if(event.type == sf::Event::MouseButtonPressed){
    mPressedMouseButtons.push_back(event.mouseButton.button);
  }


  if(event.type == sf::Event::MouseButtonReleased){
     mPressedMouseButtons.erase(std::remove(mPressedMouseButtons.begin(), mPressedMouseButtons.end(),event.mouseButton.button), mPressedMouseButtons.end());
  }

  if (event.type == sf::Event::LostFocus){
    mPressedKeys.clear();
    mPressedMouseButtons.clear();
  }

  if (event.type == sf::Event::GainedFocus){
    mPressedKeys.clear();
    mPressedMouseButtons.clear();
  }

}

void InputEngine::Update(){
  mMousePosition = sf::Mouse::getPosition(mWindow);
}

