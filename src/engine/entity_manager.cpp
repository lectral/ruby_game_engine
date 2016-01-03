#include "entity_manager.h"
#include <iostream>
#include "easylogging++.h"


EntityManager::EntityManager()
{
  mLastUsedEntity = NULL;
}


EntityManager::~EntityManager(){

}

unsigned int EntityManager::AddEntity(std::string name){
  //LOG(DEBUG) << "Entity added: "<<name;
  mEntities.push_back(Entity(mCount,name));
  mCount += 1;
  return mCount-1;
}


Entity & EntityManager::GetEntity(unsigned int id){
  if(mLastUsedEntity != NULL){
    if(mLastUsedEntity->GetID() == id){
      LOG(DEBUG) << "using last used entity";
      return *mLastUsedEntity;
    }
  }
  for(int i=0;i<mCount;i++){
    if(mEntities[i].GetID() == id){
      mLastUsedEntity = &mEntities[i];
      return mEntities[i];
    }
  }
}

Entity & EntityManager::GetEntity(std::string name){
  for(int i=0;i<mCount;i++){
    if(mEntities[i].GetName() == name){
      return mEntities[i];
    }
  }
}

void EntityManager::Update(){
  for(int i=0;i<mCount;i++){
//    mEntities[i].GetPhysical()->Move(1,0);
    mEntities[i].GetVisual()->UpdateFromPhysical(mEntities[i].GetPhysical());
  }
}