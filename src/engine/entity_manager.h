#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "entity.h"

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();
  unsigned int AddEntity(std::string name);
  
  Entity & GetEntity(unsigned int id);
  Entity & GetEntity(std::string name);
  void Update();
private:
  unsigned int mCount;
  std::vector<Entity> mEntities;
  Entity * mLastUsedEntity;
};


#endif // ENTITY_MANAGER_H
