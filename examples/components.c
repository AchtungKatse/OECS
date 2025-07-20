/**
 * @file
 * @brief 
 * \code{.c}
#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Components can be any user defined struct
typedef struct example_component {
    const char* value;
} example_component_t;

typedef struct shared_component {
    u32 value;
} shared_component_t;

// Components need to be declared so the backend can match a component name to an ID
ECS_COMPONENT_DECLARE(example_component_t); 
// This converts the above macro to the following statement:
// ecs_component_id ECS_example_component_t_ID;

// If multiple files require this component, it can be defined as
extern ECS_COMPONENT_DECLARE(shared_component_t);
// This allows the compiler to find the correct component id across several files
// Defining it here, although it could be defined in any .c or .cpp file
ECS_COMPONENT_DECLARE(shared_component_t);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Components need to be defined for each world they are in to assign them a unique id
    // This should only be done once per component
    ECS_COMPONENT_DEFINE(world, example_component_t);
    ECS_COMPONENT_DEFINE(world, shared_component_t);

    // Once a component is defined, it can be used by entities
    // For more info, see the examples/entities.c 
    // Create entity
    entity_t e = entity_create(world);

    // Set component value
    ENTITY_SET_COMPONENT(world, e, example_component_t, { .value = "This is a component" });
    ENTITY_SET_COMPONENT(world, e, shared_component_t, { .value = 0 });

    // Shutdown world
    // This will automatically free all memory used by components
    ecs_world_shutdown(world);
}
 * \endcode
 */

#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Components can be any user defined struct
typedef struct example_component {
    const char* value;
} example_component_t;

typedef struct shared_component {
    u32 value;
} shared_component_t;

// Components need to be declared so the backend can match a component name to an ID
ECS_COMPONENT_DECLARE(example_component_t); 
// This converts the above macro to the following statement:
// ecs_component_id ECS_example_component_t_ID;

// If multiple files require this component, it can be defined as
extern ECS_COMPONENT_DECLARE(shared_component_t);
// This allows the compiler to find the correct component id across several files
// Defining it here, although it could be defined in any .c or .cpp file
ECS_COMPONENT_DECLARE(shared_component_t);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Components need to be defined for each world they are in to assign them a unique id
    // This should only be done once per component
    ECS_COMPONENT_DEFINE(world, example_component_t);
    ECS_COMPONENT_DEFINE(world, shared_component_t);

    // Once a component is defined, it can be used by entities
    // For more info, see the examples/entities.c 
    // Create entity
    entity_t e = entity_create(world);

    // Set component value
    ENTITY_SET_COMPONENT(world, e, example_component_t, { .value = "This is a component" });
    ENTITY_SET_COMPONENT(world, e, shared_component_t, { .value = 0 });

    // Shutdown world
    // This will automatically free all memory used by components
    ecs_world_shutdown(world);
}

