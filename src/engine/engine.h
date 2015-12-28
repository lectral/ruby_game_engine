#ifndef ENGINE_CPP
#define ENGINE_CPP
#include <SFML/Graphics.hpp>
#include "sound_engine.h"
#include "easylogging++.h"
#include "engine/strings_manager.h"
#include "engine/input_engine.h"
#include "engine/graphics_engine.h"
#include "engine/game_engine.h"
#include "engine/mruby_binding.h"

class Engine
{
public:
   Engine();
  ~ Engine();
  void Run();
  void SetStartParameters(int res_x,int res_y);
  SoundEngine& GetSound();
  GraphicsEngine& GetGraphics();
  MRubyBinding& GetBinding();
  StringsManager& GetStrings();
private:
  sf::RenderWindow mWindow;
  sf::Vector2i mMouseXY;
  sf::Event mEvent;
  SoundEngine mSoundEngine;
  InputEngine mInputEngine;
  MRubyBinding mRubyBinding;
  StringsManager mStrings;
  GraphicsEngine mGraphicsEngine;
  bool mIsEngineRunning;
};


#endif // ENGINE_CPP
