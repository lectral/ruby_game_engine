#ifndef STRINGS_MANAGER_H
#define STRINGS_MANAGER_H
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

struct StringStruct {
   std::string name;
   std::string value;
};


class StringsManager
{
public:
  //const std::string SUPPORTED_LANGUAGES[2] = {"en","fr"};
  StringsManager();
  ~StringsManager();
  void LoadStrings(std::string module);
  std::string GetString(std::string name);
  int GetStringCount();
  void ChangeLanguage(std::string lang);
  std::string GetLanguage();
  void ClearStrings();
  void AddString(std::string name,std::string content);
private:
  int mStringCount;
  std::string mCurrentLanguage;
  std::vector<StringStruct> mStrings;
};


#endif // STRINGS_MANAGER_H
