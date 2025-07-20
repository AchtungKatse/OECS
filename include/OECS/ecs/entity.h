/**
 * @file entity.h
 * @brief Contains all functions and types for ecs entities.
 */

#pragma once

// ================================
// ECS Base Types
// ================================
#include "OECS/containers/darray.h"

typedef u64 ecs_index;
typedef ecs_index entity_t;
typedef u32 ecs_component_id;

darray_header(entity_t, entity);

#define ENTITY_SET_COMPONENT(world, entity, component, component_value) \
{ \
    component __val__ = (component)component_value; \
    entity_set_component(world, entity, ECS_COMPONENT_ID(component), &__val__, sizeof(component)); \
} 
#define ENTITY_ADD_COMPONENT(world, entity, component) \
    entity_add_component(world, entity, ECS_COMPONENT_ID(component))
#define ENTITY_GET_COMPONENT(world, entity, component) \
    (component*)entity_get_component(world, entity, ECS_COMPONENT_ID(component))
#define ENTITY_TRY_GET_COMPONENT(world, entity, component, out_value) \
    entity_try_get_component(world, entity, ECS_COMPONENT_ID(component), (void**)out_value)
#define ENTITY_HAS_COMPONENT(world, entity, component) \
    entity_has_component(world, entity, ECS_COMPONENT_ID(component))

struct ecs_world;
typedef struct ecs_world ecs_world_t;

/**
 * @brief Creates a new empty entity in a world.
 *
 * @param world The target world.
 * @return A new entity.
 */
entity_t entity_create(struct ecs_world* world);
/**
 * @brief Checks if an entity has a component. Should be accessed via the ENTITY_HAS_COMPONENT(world, entity, component) macro.
 *
 * @param world The target world.
 * @param entity The entity to check.
 * @param component The component to check.
 * @return True if the entity has a component, false if otherwise.
 */
b8 entity_has_component(struct ecs_world* world, entity_t entity, ecs_index component);
/**
 * @brief Checks if an entity has a component and returns it if so. Should be accessed via the ENTITY_TRY_GET_COMPONENT(world, entity, component, out_value) macro.
 *
 * @param world The world the entity is in.
 * @param entity The target entity.
 * @param component The target component
 * @param out_value The output component.
 * @return True if the component was successfully retrieved, false if otherwise.
 */
b8 entity_try_get_component(struct ecs_world* world, entity_t entity, ecs_index component, void** out_value);
/**
 * @brief Returns the component data from an entity. Should be accessed via the ENTITY_GET_COMPONENT(world, entity, component) macro.
 *
 * @param world The world the entity is in.
 * @param entity The target entity.
 * @param component The target component.
 */
void* entity_get_component(struct ecs_world* world, entity_t entity, ecs_index component);
/**
 * @brief Adds an uninitialized component to an entity. Should be accessed via the ENTITY_ADD_COMPONENT(world, entity, component) macro.
 *
 * @param world The world the entity is in.
 * @param entity The target entity.
 * @param component_id The target component.
 */
void entity_add_component(struct ecs_world* world, entity_t entity, ecs_component_id component_id);
/**
 * @brief Sets the value of a component for an entiy. Will add the component to an entity if it does not already have the component. Should be accessed via the ENTITY_ADD_COMPONENT(world, entity, component, value) macro.
 *
 * @param world The world the entity is in.
 * @param entity The target entity.
 * @param component The component type to be added.
 * @param data The data the component to be added.
 * @param stride The stride of the component.
 */
void entity_set_component(struct ecs_world* world, entity_t entity, ecs_component_id component, void* data, u32 stride);
