#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class InputEngine
{
public:
  InputEngine(sf::RenderWindow &window);
  ~InputEngine();
  int GetMouseX();
  int GetMouseY();
  void SetMouse(int x,int y);
  bool IsKeyPressed(sf::Keyboard::Key);
  void ProcessEvents(sf::Event & event);
private:
  void Update();
  sf::RenderWindow & mWindow;
  std::vector<int> mPressedKeys;

  
};


#endif // INPUT_ENGINE_H