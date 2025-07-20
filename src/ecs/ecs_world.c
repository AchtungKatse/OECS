#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/ecs.h"
#include "OECS/ecs/entity.h"
#include "OECS/memory/linear_allocator.h"

ecs_world_t* pvt_ecs_world;

ecs_world_t* ecs_world_initialize() {
    pvt_ecs_world = sallocate(sizeof(ecs_world_t), MEMORY_TAG_ECS);
    pvt_ecs_world->entity_count = 0;
    darray_entity_record_create(100, &pvt_ecs_world->records);
    darray_ecs_component_create(100, &pvt_ecs_world->components);
    darray_entity_archetype_create(100, &pvt_ecs_world->archetypes);
    darray_ecs_query_create(100, &pvt_ecs_world->queries);
    for (u32 i = 0; i < ECS_PHASE_ENUM_MAX; i++) {
        darray_ecs_system_create(20, &pvt_ecs_world->systems[i]);
    }

    // Create default (empty) archetype
    entity_archetype_create(pvt_ecs_world, 0, NULL, &pvt_ecs_world->archetypes.data[0]);
    pvt_ecs_world->archetypes.count = 1;

    // Create default empty component
    ecs_world_component_define(pvt_ecs_world, "Null", 0);

    return pvt_ecs_world;
}

ecs_world_t* ecs_world_get() {
    return pvt_ecs_world;
}

void ecs_world_shutdown(ecs_world_t* world) {
    for (u32 i = 0; i < world->archetypes.count; i++) {
        entity_archetype_destroy(&pvt_ecs_world->archetypes.data[i]);
    }
    for (u32 i = 0; i < world->components.count; i++) {
        darray_entity_archetype_ptr_destroy(&pvt_ecs_world->components.data[i].archetypes);
    }
    for (u32 i = 0; i < world->queries.count; i++) {
        ecs_query_destroy(&pvt_ecs_world->queries.data[i]);
    }

    for (u32 i = 0; i < ECS_PHASE_ENUM_MAX; i++) {
#ifdef SPARK_DEBUG
        for (u32 s = 0; s < pvt_ecs_world->systems[i].count; s++) {
            ecs_system_t* system = &pvt_ecs_world->systems[i].data[s];
            SDEBUG("ECS System '%s' took average of %.03fms", system->name, system->runtime / system->calls * 1000.0f);
        }
#endif
        darray_ecs_system_destroy(&pvt_ecs_world->systems[i]);
    }
    darray_ecs_query_destroy(&pvt_ecs_world->queries);
    darray_entity_record_destroy(&pvt_ecs_world->records);
    darray_ecs_component_destroy(&pvt_ecs_world->components);
    darray_entity_archetype_destroy(&pvt_ecs_world->archetypes);
}

ecs_component_id ecs_world_component_define(ecs_world_t* world, const char* name, u32 stride) {
    ecs_component_t component = {
        .stride = stride,
        .name = name,
    };
    darray_entity_archetype_ptr_create(5, &component.archetypes);

    ecs_component_id component_id = world->components.count;
    darray_ecs_component_push(&world->components, component);
    return component_id;
}

void ecs_world_progress(ecs_world_t* world) {
    for (u32 phase = 0; phase < ECS_PHASE_ENUM_MAX; phase++) {
        for (u32 i = 0; i < world->systems[phase].count; i++) {
            ecs_system_t* system = &world->systems[phase].data[i];
#ifdef SPARK_DEBUG
            spark_clock_t clock;
            clock_start(&clock);
#endif
            ecs_query_iterate(system->query, system->callback);
#ifdef SPARK_DEBUG
            clock_update(&clock);
            system->runtime += clock.elapsed_time;
            system->calls++;
#endif
        }
    }
}
