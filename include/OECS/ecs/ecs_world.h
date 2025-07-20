/**
 * @file
 * @brief Contains all functions and data for an ecs_world
 */

#pragma once

#include "OECS/ecs/ecs.h"
#include "OECS/memory/linear_allocator.h"

/**
 * @class ecs_world
 * @brief A private container for all data contained by the ecs.
 *
 */
typedef struct ecs_world {
    /**
     * @brief Number of entities inside of a world.
     */
    entity_t entity_count;
    /**
     * @brief A lookup table to match an entity to its archetype and index.
     */
    darray_entity_record_t records;
    /**
     * @brief All defined component data.
     */
    darray_ecs_component_t components;
    /**
     * @brief All existing archetypes.
     */
    darray_entity_archetype_t archetypes;
    /**
     * @brief All existing queries.
     */
    darray_ecs_query_t queries;
    /**
     * @brief An array of darrays of systems. The key to each array is an ecs_phase which allows systems to be run in a specific order.
     */
    darray_ecs_system_t systems[ECS_PHASE_ENUM_MAX];
} ecs_world_t;

/**
 * @brief Initializes an ecs_world.
 *
 * @return Valid ecs_world.
 */
ecs_world_t* ecs_world_initialize();
/**
 * @brief Returns a singleton of the ecs_world.
 */
struct ecs_world* ecs_world_get();
/**
 * @brief Shutsdown and destroys an ecs world. Frees all associated data.
 *
 * @param world The world to shutdown.
 */
void ecs_world_shutdown(ecs_world_t* world);
/**
 * @brief Runs all systems in a world.
 *
 * @param world The world to progress all systems.
 */
void ecs_world_progress(ecs_world_t* world);

/**
 * @brief Defines a component for a world. Should be called via the ECS_COMPONENT_DEFINE macro to automatically get type information.
 *
 * @param world The target world.
 * @param name The name of the component.
 * @param stride The stride of the component.
 * @return An id / index into the world's componet data array.
 */
ecs_component_id ecs_world_component_define(ecs_world_t* world, const char* name, u32 stride);

#define ECS_COMPONENT_DEFINE(world, component) ECS_COMPONENT_ID(component) = ecs_world_component_define(world, "ECSComponent_" #component "_ID", sizeof(component))
