#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "data_structs/texture_file.h"
#include "data_structs/drawable.h"
#include "data_structs/visual.h"


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
  int AddDrawable(std::string str_id,std::string texture, int layer);
  void AddVisual(std::string name,std::string texture);
  Drawable * GetDrawable(int id);
  Drawable * GetDrawable(std::string id);
  int GetDrawableCount();
  Visual & GetVisual(std::string name);
  void Update(sf::Time time);
private:
  void ExtractSizes(std::string input,unsigned int &x,unsigned int &y);
  std::vector<TextureFile> mTextures;
  sf::RenderWindow & mWindow;
  std::vector<Drawable> mDrawables;
  std::vector<Visual> mVisuals;
  int mDrawablesIndex;
  bool m2Textures;

};

#endif // GRAPHICS_ENGINE_H
