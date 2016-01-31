#include "app.h"
#include <iostream>
#include <string>
#include "engine/engine.h"
#include "engine/version.h"
#include "app/config_file.h"
#include "easylogging++.h"

App::App() :
  mEngine()
{
\
}

App::~App(){
  
}


void App::Run(){
  LOG(INFO) << "Application is starting...";
  LOG(INFO) << "Engine version: " << ENGINE_VERSION;

  // Load configuration file and set parameters
  ConfigFile config_file("configuration.yaml");
  if(config_file.IsExisting()){
     config_file.Load();
  }else{
     LOG(INFO) << "configuration.yaml does not exist... creating default...";
     config_file.CreateDefault();
     config_file.Load();
  }

  config_file.Load();
  mEngine.SetStartParameters(config_file.GetResX(),config_file.GetResY());
  
  LOG(INFO) << "configuration.yaml loaded.";
  LOG(INFO) << "Resolution: " << config_file.GetResX() << "x" << config_file.GetResY();
  
  // Start the damn thing
  mEngine.Run();
}

void App::Error(std::string error){
  LOG(ERROR) << error;
  abort();
}


Engine & App::GetEngine(){
  return mEngine;
}
