#include "engine/engine.h"
#include <iostream>

Engine::Engine() : 
  mWindow(sf::VideoMode(640, 480, 32), "hack_game",sf::Style::Close),
  mSoundEngine(),
  mGraphicsEngine(mWindow),
  mInputEngine(mWindow)

{
  mWindow.setPosition(sf::Vector2i(-500,-500));
  mIsEngineRunning = false;
}

Engine::~Engine(){

}

void Engine::SetStartParameters(int res_x,int res_y){
  mWindow.create(sf::VideoMode(res_x,res_y,32),"hack_game",sf::Style::Close);
  mWindow.setPosition(sf::Vector2i(15,10));
}


void Engine::Run(){
  LOG(DEBUG) << "Engine started!"; 
  float test=0.1;

  mIsEngineRunning = true;
  
  // Load
  mRubyBinding.InitMRuby();
  mRubyBinding.BindCpp();

  mRubyBinding.LoadEntryPoint("data/init.rb");
  mRubyBinding.Initialize();

  mSoundEngine.LoadSoundFiles();
  sf::Clock clock;
  sf::Clock frame_clock;
  sf::Clock tick;
  float lastTime = 0;
  mFPS = 0;
  int frame_count = 0;
  mWindow.setFramerateLimit(120);
  AddEngineCursor();
  while(mWindow.isOpen() && mIsEngineRunning){
    while(mWindow.pollEvent(mEvent)){
      if (mEvent.type == sf::Event::Closed) mWindow.close();
      mInputEngine.ProcessEvents(mEvent);
    }
    mFrameTime = frame_clock.restart();
    GetSound().Update();
    mInputEngine.Update();
    
    
    sf::Vector2i pixelPos = sf::Mouse::getPosition(mWindow);
    sf::Vector2f worldPos = mGraphicsEngine.GetRenderTexture().mapPixelToCoords(pixelPos);

    mEntityManager.GetEntity(mCursorId).GetPhysical()->SetPosition(worldPos.x-200,worldPos.y-200);
    mEntityManager.GetEntity(mCursorId).GetPhysical()->ClearBoundingBoxes(); 
    mEntityManager.GetEntity(mCursorId).GetPhysical()->AddBoundingBox(POINT,sf::Vector2f(worldPos.x-200,worldPos.y-200));  
    mWindow.clear();

    mRubyBinding.Update();
    mEntityManager.Update();
    mPhysicsEngine.Update();
    mGraphicsEngine.Update(clock.restart());
    mGraphicsEngine.Draw();
    mWindow.display();
    lastTime += tick.getElapsedTime().asMilliseconds();
    if(lastTime>=1000){
      lastTime = 0;
      mFPS = frame_count;
      frame_count = 0;
      LOG(INFO) << "FPS: "<< mFPS;
    } 

    tick.restart();
    frame_count+=1;
  }
  mIsEngineRunning = false;
  LOG(INFO) << "Shutdown complete.";

}

void Engine::AddEngineCursor(){
  auto physical_id = GetPhysics().AddPhysical();
  mCursorId = mEntityManager.AddEntity("ENGINE_MOUSE_CURSOR");
  mEntityManager.GetEntity(mCursorId).SetPhysical(GetPhysics().GetPhysical(physical_id));
  mEntityManager.GetEntity(mCursorId).GetPhysical()->ClearBoundingBoxes();
  mEntityManager.GetEntity(mCursorId).GetPhysical()->AddBoundingBox(POINT,sf::Vector2f(0,0));  
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

InputEngine& Engine::GetInput() {
  return mInputEngine;
}


EntityManager& Engine::GetEntities() {
  return mEntityManager;
}

PhysicsEngine& Engine::GetPhysics() {
  return mPhysicsEngine;
}

void Engine::Stop(){
  mIsEngineRunning = false;
}

sf::Time Engine::GetFrameTime(){
  return mFrameTime;
}

int Engine:: GetCurrentFPS(){

 return mFPS;
}
