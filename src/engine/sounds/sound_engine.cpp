#include "sound_engine.h"
#include <yaml-cpp/yaml.h>
#include "easylogging++.h"
#include <algorithm>


SoundEngine::SoundEngine(){
  mSoundVolume = 50;
  mMusicVolume = 50;
  mMusicPaused = true;
  mCurrentMusic.stop();
}

SoundEngine::~SoundEngine(){


}

void SoundEngine::SetMusicVolume(float volume) {
  mMusicVolume = volume;
}


void SoundEngine::SetSoundVolume(float volume) {
  mSoundVolume = volume;
}


float SoundEngine::GetMusicVolume() {
  return mMusicVolume;
}

float SoundEngine::GetSoundVolume() {
  return mSoundVolume;
}



void SoundEngine::LoadMusicFiles(std::string module){
   std::string base_path = "data/"+module;
   std::string audio_path = base_path+"/audio/";
   std::string db_path = base_path+"/db/music_db.yaml";
   std::ifstream fin(db_path);
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
   for(unsigned i=0;i<doc.size();i++) {
      std::string name;
      std::string path;
      doc[i]["name"] >> name;
      doc[i]["path"] >> path;
      mMusicFiles.push_back(SoundFile(name,audio_path+path));
   }
}


void SoundEngine::AddSoundFile(std::string module, std::string name,std::string path){
  std::string base_path = "data/"+module;
  std::string audio_path = base_path+"/audio/";
  mSoundFiles.push_back(SoundFile(name,audio_path+path));
}


void SoundEngine::AddMusicFile(std::string module, std::string name,std::string path){
  std::string base_path = "data/"+module;
  std::string audio_path = base_path+"/audio/";
  mMusicFiles.push_back(SoundFile(name,audio_path+path));
}

void SoundEngine::LoadSoundFiles(){
  for(std::vector<SoundFile>::iterator it = mSoundFiles.begin(); it != mSoundFiles.end(); ++it) {
    it->LoadFile();
  }
}


std::vector<SoundFile> SoundEngine::GetLoadedMusicFiles(){
  return mMusicFiles;
}

std::vector<SoundFile> SoundEngine::GetLoadedSoundFiles(){
  return mSoundFiles;
}

std::queue<SoundFile> SoundEngine::GetMusicQueue(){
  return mMusicQueue;
}

void SoundEngine::AddMusicToQueue(std::string music_name){
  for(std::vector<SoundFile>::iterator it = mMusicFiles.begin(); it != mMusicFiles.end(); ++it) {
    if(it->GetName()==music_name){
      mMusicQueue.push(*it);
      return;
    }
  }
  throw std::runtime_error("music file not found");
}


void SoundEngine::ClearMusicQueue(){
 while (!mMusicQueue.empty())
  {
     mMusicQueue.pop();
  }
}


void SoundEngine::PlayMusic(){
  if (!mCurrentMusic.openFromFile(mMusicQueue.front().GetPath()))
    throw;
  mCurrentMusic.play();
  mMusicQueue.pop();
  mMusicPaused = false;
}

void SoundEngine::PlaySound(std::string music_name){
  bool found = false;
  for(std::vector<SoundFile>::iterator it = mSoundFiles.begin(); it != mSoundFiles.end(); ++it) {
    if(it->GetName()== music_name){
      mCurrentSound.setBuffer(it->GetSoundBuffer());
      mCurrentSound.play();
      found = true;
      return;
    }
  }

  if(!found){
    LOG(INFO) << music_name << " sound not found";
  }

}



void SoundEngine::PlayNextSong(){
  if(!mMusicQueue.empty()){
    mCurrentMusic.stop();
    mCurrentMusic.openFromFile(mMusicQueue.front().GetPath());
    mCurrentMusic.play();
    mMusicQueue.pop();
  }
}

void SoundEngine::PauseMusic(){
  mCurrentMusic.pause();
  mMusicPaused = true;
}

bool SoundEngine::IsMusicPaused(){
  return mMusicPaused;
}


void SoundEngine::Update(){
  if(mCurrentMusic.getStatus() == sf::SoundSource::Stopped){
    PlayNextSong();
  }

}

bool SoundEngine::IsQueueEmpty(){
  mMusicQueue.empty();
}



/*
  SoundFile
*/

