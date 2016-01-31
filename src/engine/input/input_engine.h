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
  bool IsMousePressed(sf::Mouse::Button button);
  void ProcessEvents(sf::Event & event);
  void Update();
private:
  sf::RenderWindow & mWindow;
  std::vector<int> mPressedKeys;
  std::vector<int> mPressedMouseButtons;
  sf::Vector2i mMousePosition;


  
};


#endif // INPUT_ENGINE_H