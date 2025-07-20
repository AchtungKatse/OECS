/**
 * @file examples/systems.c
 * @brief An example implementation of a system which simulates an object moving upwards and being affected by gravity. \code{.c} 
#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct velocity {
    float vertical;
} velocity_t;

typedef struct height {
    float value;
} height_t;

ECS_COMPONENT_DECLARE(velocity_t);
ECS_COMPONENT_DECLARE(height_t);

void apply_gravity(ecs_iterator_t* iterator);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, velocity_t);
    ECS_COMPONENT_DEFINE(world, height_t);

    // Create an entity
    entity_t e = entity_create(world);
    ENTITY_SET_COMPONENT(world, e, height_t, { 3.0f });
    ENTITY_SET_COMPONENT(world, e, velocity_t, { 10.0f });

    // Create the system
    // Systems are a combination of a query and phase to be automatically run
    // The phase will determine when a system will get run, allowing systems to be executed 
    // in a specific order.
    ecs_query_create_info_t create_info = {
        .component_count = 2,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(velocity_t),
            ECS_COMPONENT_ID(height_t),
        },
    };

    ecs_system_create(world, ECS_PHASE_PHYSICS, &create_info, apply_gravity, "apply_gravity_system");

    // The system will then run automatically when calling ecs_world_progress
    // This example will stop when the object's position < 0
    height_t* height = ENTITY_GET_COMPONENT(world, e, height_t);
    int iteration = 0;
    while (height->value > 0) {
        SINFO("Height: %.2f", height->value);
        iteration++;

        ecs_world_progress(world);
    }
    SINFO("Height: %.2f", height->value);
}

void apply_gravity(ecs_iterator_t* iterator) {
    const float gravity = 9.81f;
    const float time_step = 0.05f;

    velocity_t* velocity = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    height_t* heights = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);

    for (u32 i = 0; i < iterator->entity_count; i++) {
        heights[i].value += velocity[i].vertical * time_step;
        velocity[i].vertical -= gravity * time_step;
    }
}
 * \endcode
 * 
 */

#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct velocity {
    float vertical;
} velocity_t;

typedef struct height {
    float value;
} height_t;

ECS_COMPONENT_DECLARE(velocity_t);
ECS_COMPONENT_DECLARE(height_t);

void apply_gravity(ecs_iterator_t* iterator);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, velocity_t);
    ECS_COMPONENT_DEFINE(world, height_t);

    // Create an entity
    entity_t e = entity_create(world);
    ENTITY_SET_COMPONENT(world, e, height_t, { 3.0f });
    ENTITY_SET_COMPONENT(world, e, velocity_t, { 10.0f });

    // Create the system
    // Systems are a combination of a query and phase to be automatically run
    // The phase will determine when a system will get run, allowing systems to be executed 
    // in a specific order.
    ecs_query_create_info_t create_info = {
        .component_count = 2,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(velocity_t),
            ECS_COMPONENT_ID(height_t),
        },
    };

    ecs_system_create(world, ECS_PHASE_PHYSICS, &create_info, apply_gravity, "apply_gravity_system");

    // The system will then run automatically when calling ecs_world_progress
    // This example will stop when the object's position < 0
    height_t* height = ENTITY_GET_COMPONENT(world, e, height_t);
    int iteration = 0;
    while (height->value > 0) {
        SINFO("Height: %.2f", height->value);
        iteration++;

        ecs_world_progress(world);
    }
    SINFO("Height: %.2f", height->value);
}

void apply_gravity(ecs_iterator_t* iterator) {
    const float gravity = 9.81f;
    const float time_step = 0.05f;

    velocity_t* velocity = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    height_t* heights = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);

    for (u32 i = 0; i < iterator->entity_count; i++) {
        heights[i].value += velocity[i].vertical * time_step;
        velocity[i].vertical -= gravity * time_step;
    }
}
