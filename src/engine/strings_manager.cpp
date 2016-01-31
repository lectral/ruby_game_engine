#include "strings_manager.h"
#include <fstream>
#include "easylogging++.h"

StringsManager::StringsManager(){
  mCurrentLanguage = "en";
}

StringsManager::~StringsManager(){
  
}


//void StringsManager::LoadStrings(std::string module){
  //ClearStrings();
  //std::ifstream fin("data/"+module+"/db/strings_db.yaml");
  //YAML::Parser parser(fin);
  //YAML::Node doc;
  //parser.GetNextDocument(doc);
  //for(unsigned i=0;i<doc.size();i++) {
    //std::string name;
    //std::string value;
    //StringStruct record;
    //doc[i]["name"] >> name;
    //doc[i][mCurrentLanguage] >> value;
    ////LOG(DEBUG) << "Loading string: "+name;
    //record.name = name;
    //record.value = value;
    //mStrings.push_back(record);
   //}
//}


void StringsManager::AddString(std::string name,std::string content){
  StringStruct record;
  record.name = name;
  record.value = content;
  mStrings.push_back(record);
  LOG(DEBUG) << "String added "<<name;
}


void StringsManager::ClearStrings(){
  mStrings.clear();
}

std::string StringsManager::GetString(std::string name){

  for(std::vector<StringStruct>::iterator it = mStrings.begin(); it != mStrings.end(); ++it) {
    //LOG(DEBUG) << "fu: "<<it->name<<" against "<<name;
    if(it->name==name){
      return it->value;
    }
  }
  return "<NO_STRING>";
}

int StringsManager::GetStringCount(){
  mStrings.size();
}

void StringsManager::ChangeLanguage(std::string lang){
  mCurrentLanguage = lang;
}

std::string StringsManager::GetLanguage(){
  return mCurrentLanguage;
}
