#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <yaml-cpp/yaml.h>

class ConfigFile
{
public:
   ConfigFile(std::string path);
  ~ConfigFile();
  int GetResX();
  int GetResY();
  bool IsExisting();
  void Load();
  void CreateDefault();
private:
  int mResX;
  int mResY;
  std::string mPath;
};


#endif // CONFIG_FILE_H
