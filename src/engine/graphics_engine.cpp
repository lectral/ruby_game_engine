#include "graphics_engine.h"
#include <yaml-cpp/yaml.h>
#include "easylogging++.h"
#include <algorithm>

GraphicsEngine::GraphicsEngine(sf::RenderWindow &window ) : 
  mWindow(window)
{

  mDrawablesIndex = 0;

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

void GraphicsEngine::LoadVisuals(std::string module){
  // std::ifstream fin("data/"+module+"/db/visuals_db.yaml");
  //  YAML::Parser parser(fin);
  //  YAML::Node doc;
  //  parser.GetNextDocument(doc);
  //  for(unsigned i=0;i<doc.size();i++) {
  //     std::string name;
  //     std::string texture;
  //     std::string size;
  //     unsigned int it=0,sizex,sizey;
  //     doc[i]["name"] >> name;
  //     doc[i]["texture"] >> texture;
  //     doc[i]["size"] >> size;
  //     ExtractSizes(size,sizex,sizey);
  //     Visual tmp(name,GetTexture(texture));
  //     tmp.SetSize(sizex,sizey);
  //     for(unsigned j=0;j<doc[i]["animations"].size();j++){
  //       std::string anim_name;
  //       int start,stop;
  //       doc[i]["animations"][j]["name"] >> anim_name;
  //       doc[i]["animations"][j]["start"] >> start;
  //       doc[i]["animations"][j]["stop"] >> stop;
  //       tmp.AddAnimation(anim_name,start,stop);
  //     }
  //     mVisuals.push_back(tmp);

  //  }

}


void GraphicsEngine::AddVisual(std::string name,std::string texture){
  Visual tmp(name,GetTexture(texture));
  mVisuals.push_back(tmp);
  LOG(DEBUG)<<"Visual added: " << name;
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


Visual & GraphicsEngine::GetVisual(std::string name){
  for(int i=0;i<mVisuals.size();i++){
    if(mVisuals[i].GetName()==name){
      return mVisuals[i];
    }
  }
}


int GraphicsEngine::GetDrawableCount(){
  return mDrawables.size();
}


int GraphicsEngine::AddDrawable(std::string str_id,std::string visual,int layer){
  mDrawables.push_back(Drawable(mDrawablesIndex,str_id,GetVisual(visual),layer));
  mDrawablesIndex+=1;
  return mDrawablesIndex-1;
}


Drawable * GraphicsEngine::GetDrawable(int id){
   for(int count=0; count <= mDrawables.size(); count++) {
    if(mDrawables[count].GetID() == id){
     return &mDrawables[count];
   }
  }
}

Drawable * GraphicsEngine::GetDrawable(std::string id){
   for(int count=0; count <= mDrawables.size(); count++) {
    if(mDrawables[count].GetStringID() == id){
     return &mDrawables[count];
   }
  }
}


void GraphicsEngine::Draw(){
 for(int l=99;l>0;l--){
   for(std::vector<Drawable>::iterator it = mDrawables.begin(); it != mDrawables.end(); ++it) {
      if(it->GetLayer()==l){
        if(it->IsHidden()) continue;
        mWindow.draw(it->GetSprite());
      }
    }
  }
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
  for(int count=0; count < mDrawables.size(); count++) {
     mDrawables[count].Update(time);
   }
}
//[TO-DO] implement non high-res textures
bool  GraphicsEngine::HiResTextures(){
  return true;
}