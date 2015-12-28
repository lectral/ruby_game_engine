#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <string>


class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  void Update();
  void InitMruby();
  bool IsRubyInitialized();
  void LoadScripts();
private:
  std::string mScripts;

};



#endif // GAME_ENGINE_H
