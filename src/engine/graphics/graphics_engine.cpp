#include "graphics_engine.h"
#include <yaml-cpp/yaml.h>
#include "easylogging++.h"
#include <algorithm>
#include <engine/entities/entity.h>

GraphicsEngine::GraphicsEngine(sf::RenderWindow &window ) : 
  mWindow(window)
{

  mVisualsIndex = 0;
  mDrawablesIndex = 0;
  mRenderTexture.create(mWindow.getSize().x,mWindow.getSize().y);
  mMainView.reset(sf::FloatRect(0,0,mWindow.getSize().x,mWindow.getSize().y));
  mMainView.setViewport(sf::FloatRect(0, 0, 1, 1));
  mFont.loadFromFile("data/core/fonts/OpenSans-Regular.ttf");
  //mMainView.reset(sf::FloatRect(0,0,300,300));
  //mMainView.setSize(100, 100);
}

GraphicsEngine::~GraphicsEngine(){

}


void GraphicsEngine::LoadTexturesDb(std::string module){
   std::ifstream fin("data/"+module+"/db/texture_db.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
   for(unsigned i=0;i<doc.size();i++) {
      std::string name;
      std::string path;
      doc[i]["name"] >> name;
      doc[i]["path"] >> path;
      mTextures.push_back(TextureFile(name,"data/"+module+"/textures/"+path));
   }
}

void GraphicsEngine::AddTextureFile(std::string module,std::string name,std::string path){
   mTextures.push_back(TextureFile(name,"data/"+module+"/textures/"+path));
   LOG(DEBUG) << "Texture file addded: "<<name;
}



void GraphicsEngine::LoadTexture(std::string name){
  for(std::vector<TextureFile>::iterator it = mTextures.begin(); it != mTextures.end(); ++it) {
    if(it->GetName() == name){
      it->Load();
      break;
    }
  }
}


int GraphicsEngine::GetTextureCount(){
  return mTextures.size();
}

sf::Texture & GraphicsEngine::GetTexture(std::string name){
  for(std::vector<TextureFile>::iterator it = mTextures.begin(); it != mTextures.end(); ++it) {
    if(it->GetName() == name){
     return it->GetTexture();
    }
  }
}


int GraphicsEngine::GetVisualCount(){
  return mVisuals.size();
}



int GraphicsEngine::AddVisual(std::string str_id,std::string texture){
  mVisuals.push_back(Visual(mVisualsIndex,str_id,GetTexture(texture)));
  mVisualsIndex+=1;
  return mVisualsIndex-1;
}

unsigned int GraphicsEngine::AddDrawable(std::string visual){
  mDrawables.push_back(new Animated(mDrawablesIndex,GetVisual(visual)));
  mDrawablesIndex+=1;
  return mDrawablesIndex-1;
}


Visual & GraphicsEngine::GetVisual(int id){
   for(auto it= mVisuals.begin(); it != mVisuals.end(); ++it) {
    if(it->GetID() == id){
     return *it;
   }
  }
}

Animated * GraphicsEngine::GetDrawable(int id){
   for(auto it= mDrawables.begin(); it != mDrawables.end(); ++it) {
    if((*it)->GetID() == id){
     return *it;
   }
  }
}


Visual & GraphicsEngine::GetVisual(std::string id){
for(auto it= mVisuals.begin(); it != mVisuals.end(); ++it) {
    if(it->GetName() == id){
     return *it;
   }
  }
}


void GraphicsEngine::Draw(){
 mRenderTexture.clear();
 mWindow.clear();
 mRenderTexture.setView(mMainView);
 sf::Text my_text;
 my_text.setFont(mFont);
 my_text.setCharacterSize(50);
 my_text.setColor(sf::Color::Red); 
 my_text.setPosition(250,250);
 my_text.setString("DUPA3");
 for(int l=99;l>0;l--){
 
   for(auto it = mDrawables.begin(); it != mDrawables.end(); ++it) {
      if((*it)->GetLayer()==l){
        if((*it)->IsHidden()) continue;
        //sf::Vector2f worldPos = mWindow.mapPixelToCoords((*it)->GetCoords());
        sf::Vector2f a;
        a.x = 200;
        a.y = 200;
        (*it)->UpdateCoords(a);
        mRenderTexture.draw(*((*it)->GetDrawable()));
      }
    }
   for (auto it = mTexts.begin(); it != mTexts.end(); ++it) {
     if(it->IsHidden()) continue;
     if(it->GetLayer() == l){
       sf::Vector2f a;
       a.x = 200;
       a.y = 200;
       it->UpdateCoords(a);
       mRenderTexture.draw(*(it->GetDrawable()));       
       
     } 
   }
  }

  //mRenderTexture.draw(my_text);
  sf::Sprite sprite(mRenderTexture.getTexture());
  mRenderTexture.display();
  
  mWindow.draw(sprite);
}


void GraphicsEngine::ExtractSizes(std::string input,unsigned int &x,unsigned int &y){
  size_t pos = 0;
  int it=0;
  std::string token;
  std::string delimiter = "x";
  while ((pos = input.find(delimiter)) != std::string::npos) {
    token = input.substr(0, pos);
    if(it==0){
      x = std::stoi(token);
    }
    input.erase(0, pos + delimiter.length());
    it++;
  }
  y = std::stoi(input);
}

void  GraphicsEngine::Update(sf::Time time){
  if(mWindow.getSize().x != mRenderTexture.getSize().x){
    mRenderTexture.create(mWindow.getSize().x,mWindow.getSize().y);
    mMainView.reset(sf::FloatRect(200,200,mWindow.getSize().x,mWindow.getSize().y));

  }
  for(auto it = mDrawables.begin();it != mDrawables.end();++it) {
     (*it)->Update(time);
   }
}
//[TO-DO] implement non high-res textures
bool  GraphicsEngine::HiResTextures(){
  return true;
}

sf::View & GraphicsEngine::GetMainView(){
  return mMainView;
}

sf::RenderTexture & GraphicsEngine::GetRenderTexture(){
  return mRenderTexture;
}

Text * GraphicsEngine::AddText(){
  Text test1(1);
  test1.SetText("hello!");
  mTexts.push_back(Text(mTextsIndex));
  mTexts.back().SetFont(mFont);
  mTexts.back().SetText("dupa2");  
  mTextsIndex += 1;
  return &mTexts.back();
}

