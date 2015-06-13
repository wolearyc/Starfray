#include "entity_manager.h"
void init_entity_manager(EntityManager* target)
{
    for(int i = 0; i < 100; i++)
        target->entities[i].id = -1;
    target->max_index = 0;
    target->free_indexes = malloc(sizeof(int));
    target->free_indexes = 0;
    target->num_free_indexes = 0;
}
void add_entity(EntityManager* manager, Entity* entity)
{
    int entity_id;
    if(manager->num_free_indexes > 0)
    {
        manager->num_free_indexes--;
        entity_id = manager->free_indexes[manager->num_free_indexes];
        if(manager->num_free_indexes == 0)
        {
            free(manager->free_indexes);
            manager->free_indexes = 0;
        }
        else
            manager->free_indexes = realloc(manager->free_indexes, sizeof(int) *
                                            manager->num_free_indexes);
    }
    else if(manager->max_index == 100)
        return;
    else
    {
        entity_id = manager->max_index;
        manager->max_index++;
    }
    entity->id = entity_id;
    updt_entity(manager, *entity);
}
void updt_entity(EntityManager* manager, Entity entity)
{
    manager->entities[entity.id] = entity;
}
void remove_entity(EntityManager* manager, int entity_id)
{
    manager->entities[entity_id].id = -1;
    manager->num_free_indexes++;
    manager->free_indexes = realloc(manager->free_indexes,
                                    manager->num_free_indexes * sizeof(int));
    manager->free_indexes[manager->num_free_indexes-1] = entity_id;
}
void free_entity_manager(EntityManager* target)
{
    target->max_index = 0;
    free(target->free_indexes); target->free_indexes = 0;
    target->num_free_indexes = 0;
}