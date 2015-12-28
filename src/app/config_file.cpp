#include "config_file.h"
#include <fstream>


ConfigFile::ConfigFile(std::string path):
  mPath(path)
{

}

ConfigFile::~ConfigFile(){

}

bool ConfigFile::IsExisting(){
  std::ifstream fin(mPath);
  if(fin.is_open())
  {
    return true;
  }else {
    return false;
  }
  fin.close();
}

void ConfigFile::CreateDefault(){
  std::string def = "---\nresolution_x: 1366\nresolution_y: 768";
  std::ofstream myfile;
  myfile.open (mPath);
  myfile << def;
  myfile.close();
}

int ConfigFile::GetResX(){
  return mResX;
}

int ConfigFile::GetResY(){
  return mResY;
}

void ConfigFile::Load(){
   std::ifstream fin(mPath);
     YAML::Parser parser(fin);
     YAML::Node doc;
     parser.GetNextDocument(doc);
     doc["resolution_x"] >> mResX;
     doc["resolution_y"] >> mResY;
     fin.close();
}