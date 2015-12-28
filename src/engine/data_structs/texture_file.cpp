#include "texture_file.h"

TextureFile::TextureFile(std::string name, std::string path){
  mName = name;
  mPath = path;
}

TextureFile::~TextureFile(){

}




std::string TextureFile::GetPath(){
  return mPath;
}

void TextureFile::Load(){
  mTexture.loadFromFile(GetPath());
}

sf::Texture & TextureFile::GetTexture(){
  return mTexture;
}

std::string TextureFile::GetName(){
  return mName;
}

