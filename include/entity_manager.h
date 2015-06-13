#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "entity.h"
typedef struct EntityManager
{
    Entity entities[100]; /* indexed by entity id */
    int max_index;
    int* free_indexes;
    int num_free_indexes;
} EntityManager;
void init_entity_manager(EntityManager* target);
void add_entity(EntityManager* manager, Entity* entity);
void updt_entity(EntityManager* manager, Entity entity);
void remove_entity(EntityManager* manager, int entity_id);
void free_entity_manager(EntityManager* target);
#endif