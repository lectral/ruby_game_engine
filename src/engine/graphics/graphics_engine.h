#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "texture_file.h"
#include "visual.h" 
#include "engine/physics/physical.h"
#include "drawable.h"
#include "visual_object.h"
#include "animated.h"
#include "text.h"

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
  Visual & GetVisual(int id);
  Animated * GetDrawable(int id);
  int GetVisualCount();
  unsigned int AddDrawable(std::string visual);
  Visual & GetVisual(std::string name);
  void Update(sf::Time time);
  sf::View & GetMainView();
  Text * AddText();
  sf::RenderTexture & GetRenderTexture();
private:
  void ExtractSizes(std::string input,unsigned int &x,unsigned int &y);
  std::vector<TextureFile> mTextures;
  sf::RenderWindow & mWindow;
  std::list<Visual> mVisuals;
  std::list<Animated> mAnimatedVisuals;
  std::list<Animated*> mDrawables;
  std::list<Text> mTexts;
  unsigned int mVisualsIndex;
  unsigned int mDrawablesIndex;
  unsigned int mTextsIndex;
  bool m2Textures;
  sf::RenderTexture mRenderTexture;
  sf::View mMainView;
  sf::Font mFont;

};
#endif // GRAPHICS_ENGINE_H
