#include "sound_file.h"

SoundFile::SoundFile(std::string name,std::string path){
  mName = name;
  mPath = path;
}

SoundFile::~SoundFile(){


}


std::string SoundFile::GetPath(){
  return mPath;
}

std::string SoundFile::GetName(){
  return mName;
}

void SoundFile::LoadFile(){
  mBuffer.loadFromFile(GetPath());
}

sf::SoundBuffer& SoundFile::GetSoundBuffer(){
  return mBuffer;
}

