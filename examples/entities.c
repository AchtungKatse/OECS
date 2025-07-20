/**
 * @file examples/entities.c
 * @brief Examlpes on how to create and modify entities \code{.c}
#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct counter {
    int count;
} counter_t;
ECS_COMPONENT_DECLARE(counter_t); 

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, counter_t);

    // Create entity
    entity_t e = entity_create(world);

    // Check if entity has a component
    if (ENTITY_HAS_COMPONENT(world, e, counter_t)) {
        SINFO("Entity initialized with counter component");
    } else {
        SINFO("Entity is not initialized with counter component");
    }

    // Add a component
    // This will allocate the memory used by the component and initialize all values to zero
    ENTITY_ADD_COMPONENT(world, e, counter_t);

    // Set component value
    // NOTE: This will add the component to the entity if it has not already added
    ENTITY_SET_COMPONENT(world, e, counter_t, { .count = 0 });

    // Check if entity has a component
    if (ENTITY_HAS_COMPONENT(world, e, counter_t)) {
        SINFO("Entity now has counter component.");
    } else {
        SINFO("Entity did not add counter component.");
    }

    // Get the value of a component
    counter_t* counter = ENTITY_GET_COMPONENT(world, e, counter_t);
    SINFO("Initial counter value: %d", counter->count);

    // Update the value of a component
    // Option 1: Modify via a pointer from ENTITY_GET_COMPONENT
    counter->count = 1;
    SINFO("Counter updated via option 1: %d", counter->count);

    // Option 2: Update the value via ENTITY_SET_COMPONENT
    // NOTE: Values not defined will be reset to zero
    ENTITY_SET_COMPONENT(world, e, counter_t, { .count = 2 });
    SINFO("Counter updated via option 1: %d", counter->count);

    // Shutdown world
    ecs_world_shutdown(world);
}
 * \endcode
 */

#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct counter {
    int count;
} counter_t;
ECS_COMPONENT_DECLARE(counter_t); 

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, counter_t);

    // Create entity
    entity_t e = entity_create(world);

    // Check if entity has a component
    if (ENTITY_HAS_COMPONENT(world, e, counter_t)) {
        SINFO("Entity initialized with counter component");
    } else {
        SINFO("Entity is not initialized with counter component");
    }

    // Add a component
    // This will allocate the memory used by the component and initialize all values to zero
    ENTITY_ADD_COMPONENT(world, e, counter_t);

    // Set component value
    // NOTE: This will add the component to the entity if it has not already added
    ENTITY_SET_COMPONENT(world, e, counter_t, { .count = 0 });

    // Check if entity has a component
    if (ENTITY_HAS_COMPONENT(world, e, counter_t)) {
        SINFO("Entity now has counter component.");
    } else {
        SINFO("Entity did not add counter component.");
    }

    // Get the value of a component
    counter_t* counter = ENTITY_GET_COMPONENT(world, e, counter_t);
    SINFO("Initial counter value: %d", counter->count);

    // Update the value of a component
    // Option 1: Modify via a pointer from ENTITY_GET_COMPONENT
    counter->count = 1;
    SINFO("Counter updated via option 1: %d", counter->count);

    // Option 2: Update the value via ENTITY_SET_COMPONENT
    // NOTE: Values not defined will be reset to zero
    ENTITY_SET_COMPONENT(world, e, counter_t, { .count = 2 });
    SINFO("Counter updated via option 1: %d", counter->count);

    // Shutdown world
    ecs_world_shutdown(world);
}
