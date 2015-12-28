#ifndef SOUND_FILE_H
#define SOUND_FILE_H
#include <SFML/Audio.hpp>


struct SoundFile {
  SoundFile(std::string name,std::string path);
  ~SoundFile();
public:
  std::string GetName();
  std::string GetPath();
  sf::SoundBuffer& GetSoundBuffer();
  void LoadFile();
private:
  std::string mName;
  std::string mPath;
  sf::SoundBuffer mBuffer;

};


#endif // SOUND_FILE_H


