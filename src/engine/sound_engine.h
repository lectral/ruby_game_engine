#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <vector>
#include <queue>
#include <string>
#include <SFML/Audio.hpp>

#include "data_structs/sound_file.h"


class SoundEngine
{
public:
  SoundEngine();
  ~ SoundEngine();
  void SetMusicVolume(float volume);
  void SetSoundVolume(float volume);
  float GetSoundVolume();
  float GetMusicVolume();
  // Common
  void AddMusicFile(std::string module,std::string name,std::string path);
  void AddSoundFile(std::string module,std::string name,std::string path);
  void LoadMusicFiles(std::string module);
  void LoadSoundFiles();
  std::vector<SoundFile> GetLoadedMusicFiles();
  std::vector<SoundFile> GetLoadedSoundFiles();
  std::queue<SoundFile> GetMusicQueue();
  //Music
  void AddMusicToQueue(std::string music_name);
  void PlayNextSong();
  void PauseMusic();
  void PlaySound(std::string music_name);
  bool IsMusicPaused();
  void ClearMusicQueue();
  void PlayMusic();
  void Update();
  bool IsQueueEmpty();
  //Sounds
  // [TO-DO]

private:
  std::queue<SoundFile> mMusicQueue;
  std::vector<SoundFile> mMusicFiles;
  std::vector<SoundFile> mSoundFiles;
  bool mMusicPaused;
  float mMusicVolume;
  float mSoundVolume;
  sf::Music mCurrentMusic;
  sf::Sound mCurrentSound;



};




#endif // SOUND_ENGINE_H
