#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "entity.h"
#include <list>

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();
  unsigned int AddEntity(std::string name);
  
  Entity & GetEntity(unsigned int id);
  //Entity & GetEntity(std::string name);
  void Update();
private:
  unsigned int mCount;
  std::list<Entity> mEntities;
  std::list<Entity>::iterator  mLastUsedEntity;
  Entity * mLastUsedEntity2;
  std::map <unsigned int, Entity*> mEntitiesMap;

};


#endif // ENTITY_MANAGER_H
