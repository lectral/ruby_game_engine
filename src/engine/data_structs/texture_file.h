#ifndef TEXTURE_FILE_H
#define TEXTURE_FILE_H
#include <SFML/Graphics.hpp>

class TextureFile {
public:
  TextureFile(std::string name,std::string path);
  ~TextureFile();
  std::string GetName();
  std::string GetPath();
  sf::Texture & GetTexture();
  void Load();
private:
  std::string mName;
  std::string mPath;
  sf::Texture mTexture;
};


#endif // TEXTURE_FILE_H


