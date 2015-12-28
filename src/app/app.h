#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "engine/engine.h"

class App{
public:
  App();
  ~App();
  void Run();
  bool IsRunning();
  Engine & GetEngine();
  void Error(std::string error);
private:
  Engine mEngine;
  

};

extern App gApp;

#endif // APP_H