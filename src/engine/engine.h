#ifndef ENGINE_CPP
#define ENGINE_CPP
#include <SFML/Graphics.hpp>
#include "engine/sounds/sound_engine.h"
#include "easylogging++.h"
#include "engine/strings_manager.h"
#include "engine/input/input_engine.h"
#include "engine/graphics/graphics_engine.h"
#include "engine/game_engine.h"
#include "engine/mruby/mruby_binding.h"
#include "engine/entities/entity_manager.h"
#include "engine/physics/physics_engine.h"

class Engine
{
public:
   Engine();
  ~ Engine();
  void Run();
  void SetStartParameters(int res_x,int res_y);
  void Stop();
  SoundEngine& GetSound();
  GraphicsEngine& GetGraphics();
  MRubyBinding& GetBinding();
  StringsManager& GetStrings();
  InputEngine& GetInput();
  EntityManager & GetEntities();
  PhysicsEngine & GetPhysics();
  sf::Time GetFrameTime();
  int GetCurrentFPS();
private:
  void AddEngineCursor();
  int mCursorId;
  sf::RenderWindow mWindow;
  sf::Vector2i mMouseXY;
  sf::Event mEvent;
  SoundEngine mSoundEngine;
  InputEngine mInputEngine;
  MRubyBinding mRubyBinding;
  StringsManager mStrings;
  GraphicsEngine mGraphicsEngine;
  EntityManager mEntityManager;
  PhysicsEngine mPhysicsEngine;
  bool mIsEngineRunning;
  sf::Time mFrameTime;
  int mFPS;
};


#endif // ENGINE_CPP
