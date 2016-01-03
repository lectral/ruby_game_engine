#include "graphics_engine.h"
#include <yaml-cpp/yaml.h>
#include "easylogging++.h"
#include <algorithm>

GraphicsEngine::GraphicsEngine(sf::RenderWindow &window ) : 
  mWindow(window)
{

  mVisualsIndex = 0;
  mRenderTexture.create(500,500);

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


Visual * GraphicsEngine::GetVisual(int id){
   for(int count=0; count <= mVisuals.size(); count++) {
    if(mVisuals[count].GetID() == id){
     return &mVisuals[count];
   }
  }
  return NULL;
}

Visual * GraphicsEngine::GetVisual(std::string id){
   for(int count=0; count <= mVisuals.size(); count++) {
    if(mVisuals[count].GetName() == id){
     return &mVisuals[count];
   }
  }
}


void GraphicsEngine::Draw(){
 mRenderTexture.clear();
 for(int l=99;l>0;l--){
   for(std::vector<Visual>::iterator it = mVisuals.begin(); it != mVisuals.end(); ++it) {
      if(it->GetLayer()==l){
        if(it->IsHidden()) continue;
        mRenderTexture.draw(it->GetSprite());
      }
    }
  }

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
  for(int count=0; count < mVisuals.size(); count++) {
     mVisuals[count].Update(time);
   }
}
//[TO-DO] implement non high-res textures
bool  GraphicsEngine::HiResTextures(){
  return true;
}