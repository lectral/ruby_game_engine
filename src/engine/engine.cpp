#include "engine/engine.h"
#include <iostream>
#include "data_structs/visual.h"

Engine::Engine() : 
  mWindow(sf::VideoMode(640, 480, 32), "hack_game",sf::Style::Close),
  mSoundEngine(),
  mGraphicsEngine(mWindow)
{
  //mShape.setFillColor(sf::Color::Green);
  mIsEngineRunning = false;
}

Engine::~Engine(){

}

void Engine::SetStartParameters(int res_x,int res_y){
  mWindow.create(sf::VideoMode(res_x,res_y,32),"hack_game",sf::Style::Close);
}


void Engine::Run(){
  LOG(DEBUG) << "Engine started!";
  float test=0.1;
  mIsEngineRunning = true;
  
  // Load
  mRubyBinding.InitMRuby();
  mRubyBinding.BindCpp();

  mRubyBinding.LoadScript("data/core/init.rb");
  mRubyBinding.LoadScript("data/core/db/db.rb");
  mRubyBinding.LoadScript("data/core/db/string.db.rb");
  mRubyBinding.LoadScript("data/core/db/texture.db.rb");
  mRubyBinding.LoadScript("data/core/db/sound.db.rb");
  mRubyBinding.LoadScript("data/core/db/music.db.rb");
  mRubyBinding.LoadEntryPoint("data/core/scripts/entry.rb");
  mRubyBinding.Initialize();

  mSoundEngine.LoadSoundFiles();

  sf::Clock clock;
  sf::Clock tick;
  float lastTime = 0;
  int fps = 0;
  int frame_count = 0;
  mWindow.setFramerateLimit(120);
  while(mWindow.isOpen()){
    while(mWindow.pollEvent(mEvent)){
      if (mEvent.type == sf::Event::Closed) mWindow.close();
    }

    GetSound().Update();
    mMouseXY = sf::Mouse::getPosition(mWindow);
    mWindow.clear();
    mRubyBinding.Update();
    mGraphicsEngine.Update(clock.restart());
    mGraphicsEngine.Draw();
    mWindow.display();
    lastTime += tick.getElapsedTime().asMilliseconds();
    if(lastTime>=1000){
      lastTime = 0;
      fps = frame_count;
      frame_count = 0;
      LOG(INFO) << "frame count: "<<fps;
    } 

    tick.restart();
    frame_count+=1;
  }
  mIsEngineRunning = false;

}



SoundEngine& Engine::GetSound() {
  return mSoundEngine;
}

GraphicsEngine& Engine::GetGraphics() {
  return mGraphicsEngine;
}

MRubyBinding& Engine::GetBinding() {
  return mRubyBinding;
}

StringsManager& Engine::GetStrings() {
  return mStrings;
}