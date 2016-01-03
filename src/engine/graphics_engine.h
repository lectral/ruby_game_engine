#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "data_structs/texture_file.h"
#include "visual.h"
#include "physical.h"


class GraphicsEngine
{

public:
   GraphicsEngine(sf::RenderWindow & window);
  ~ GraphicsEngine();
  void Draw();
  void LoadTexturesDb(std::string module);
  void AddTextureFile(std::string module,std::string name,std::string path);
  void LoadVisuals(std::string module);
  void LoadTexture(std::string name);
  int GetTextureCount();
  bool HiResTextures();
  sf::Texture & GetTexture(std::string name);
  int AddVisual(std::string name,std::string texture);
  Visual * GetVisual(int id);
  int GetVisualCount();
  Visual * GetVisual(std::string name);
  void Update(sf::Time time);
private:
  void ExtractSizes(std::string input,unsigned int &x,unsigned int &y);
  std::vector<TextureFile> mTextures;
  sf::RenderWindow & mWindow;
  std::vector<Visual> mVisuals;
  int mVisualsIndex;
  bool m2Textures;
  sf::RenderTexture mRenderTexture;

};

#endif // GRAPHICS_ENGINE_H
