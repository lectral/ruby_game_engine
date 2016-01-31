#include "entity_manager.h"
#include <iostream>
#include "easylogging++.h"
#include <algorithm>
#include <chrono>

EntityManager::EntityManager()
{
  mLastUsedEntity = mEntities.end();
}


EntityManager::~EntityManager(){

}

unsigned int EntityManager::AddEntity(std::string name){
  //LOG(DEBUG) << "Entity added: "<<name;
  mEntities.push_back(Entity(mCount,name));
  //mLastUsedEntity = mEntities.end();
  mEntitiesMap[mCount] = &mEntities.back();
  mLastUsedEntity2 = mEntitiesMap[mCount];
  mCount += 1;
  return mCount-1;
}


Entity & EntityManager::GetEntity(unsigned int id){
  
  // if(mLastUsedEntity2->GetID() == id){
  //   return *mLastUsedEntity2;
  // }
  
  mLastUsedEntity2 = mEntitiesMap[id];
  return *mLastUsedEntity2;
}




// Entity & EntityManager::GetEntity(unsigned int id){
//   for(auto entity = mEntities.begin(); entity != mEntities.end(); ++entity) {
//     if(entity->GetID()==id){
//       return *entity;
//     }
//   }
// }

// Entity & EntityManager::GetEntity(std::string name){
//   std::vector<Entity>::iterator it;
//   it = std::find(mEntities.begin(),mEntities.end(),0);
//   return *it;
// }zz

void EntityManager::Update(){
  for(auto entity = mEntities.begin(); entity != mEntities.end(); ++entity){
//    mEntities[i].GetPhysical()->Move(1,0);
    if(entity->GetVisual() != NULL){
      entity->GetVisual()->UpdateFromPhysical(entity->GetPhysical());
    }

    if(entity->GetTexted() != NULL){
      entity->GetTexted()->UpdateFromPhysical(entity->GetPhysical());
    }
  }
}

// void EntityManager::Update(){
//   for(auto entity = mEntities.begin(); entity != mEntities.end(); ++entity) {
//     entity->GetVisual()->UpdateFromPhysical(entity->GetPhysical());
//   }
// }
