#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H
#include <SFML/Window.hpp>

class InputEngine
{
public:
  InputEngine();
  ~InputEngine();
  int GetMouseX();
  int GetMouseY();
  void SetMouse(int x,int y);
  bool IsKeyPressed(sf::Keyboard::Key);
private:
  void Update();
  //void ListenOn(sf::Window & window);


  
};


#endif // INPUT_ENGINE_H