#pragma once
#include "OECS/containers/darray.h"
#include "OECS/containers/generic/darray_ints.h"
#include "OECS/containers/set.h"
#include "OECS/containers/unordered_map.h"
#include "OECS/ecs/entity.h"


// ================================
// Forward declarations
// ================================
/**
 * @class ecs_world
 * @brief The container for all ecs data.
 *
 */
struct ecs_world;
/**
 * @class entity_archetype
 * @brief A dynamically created container for an entity with a specific set of components
 *
 */
struct entity_archetype;

set_header(ecs_component_id, ecs_component_set);

// ================================
// ECS Phases
// ================================
/**
 * @typedef ecs_phase
 * @brief The phases of the ECS pipeline. These are executed in order of lowest phase to highest phase.
 *
 */
typedef enum ecs_phase {
    ECS_PHASE_PHYSICS, 
    ECS_PHASE_PRE_UPDATE, 
    ECS_PHASE_UPDATE, 
    ECS_PHASE_POST_UPDATE, 
    ECS_PHASE_TRANSFORM, 
    ECS_PHASE_PRE_RENDER, 
    ECS_PHASE_RENDER, 
    ECS_PHASE_POST_RENDER, 
    ECS_PHASE_ENUM_MAX,
} ecs_phase_t;

// ================================
// Column
// ================================
/**
 * @typedef ecs_column
 * @brief Contains a packed array of component data. An archetype will have one column per component.
 *
 */
typedef struct ecs_column {
    void* data;
    ecs_index component_stride;
    ecs_index count;
    ecs_index capacity;
} ecs_column_t;

#define ECS_COLUMN_RESIZE_FACTOR 2
/**
 * @brief Creates a component column.
 *
 * @param initial_count The initial count of the column. Will be dynamically resized if data is added that excedes the current capacity.
 * @param component_stride The stride of the component the column represents.
 * @param out_column The output column.
 */
void ecs_component_column_create(u32 initial_count, u32 component_stride, ecs_column_t* out_column);
/**
 * @brief Destroys a column and frees its data.
 *
 * @param column The column to be destroyed
 */
void ecs_component_column_destroy(ecs_column_t* column);
/**
 * @brief Resizes a column to contain size number of elements.
 *
 * @param column The column to be resized.
 * @param size The new number of elements of the column.
 */
void ecs_component_column_resize(ecs_column_t* column, u32 size);
/**
 * @brief Pushes a new component into a column. The column may be resized if required.
 *
 * @param column The target column.
 * @param data A pointer to the component to be added.
 */
void ecs_component_column_push(ecs_column_t* column, void* data);
/**
 * @brief Removes a component from a column.
 *
 * @param column The target column.
 * @param row The index of the component to be removed.
 */
void ecs_component_column_pop (ecs_column_t* column, ecs_index row);

darray_header(ecs_column_t, ecs_column);

// ================================
// ECS Record
// ================================
/**
 * @class ecs_record
 * @brief Matches an entity to an index of a specific archetype.
 *
 */
typedef struct ecs_record {
    ecs_index index;
    u32 archetype_index;
} entity_record_t;
darray_header(entity_record_t, entity_record);

// ================================
// Entity Archetype Edge
// ================================
struct entity_archetype;
darray_header(struct entity_archetype*, entity_archetype_ptr);
hashmap_header(ecs_component_id, struct entity_archetype*, entity_archetype_ptr_map);

/**
 * @typedef entity_archetype_edge
 * @brief A lookup table to quickly match entities into new archetypes when a component is added or removed.
 *
 */
typedef struct entity_archetype_edge {
    entity_archetype_ptr_map_t add_edges;
    entity_archetype_ptr_map_t remove_edges;
} entity_archetype_edge_t;

// ================================
// Entity Archetype
// ================================
/**
 * @typedef entity_archetype
 * @brief Contains all data for a collection of entities with a specific set of components. Created and managed dynamically by the ecs_world.
 *
 */
typedef struct entity_archetype {
    /**
     * @brief The components in the archetype 
     */
    ecs_component_set_t component_set;
    /**
     * @brief The component data for each entity.
     */
    darray_ecs_column_t columns;
    /**
     * @brief A list of entities in the archetype.
     */
    darray_entity_t entities;
    /**
     * @brief Edges to similar archetypes. Used to quiclky move entities when adding or removing components
     */
    entity_archetype_edge_t edges;
    /**
     * @brief The id for the archetype.
     */
    ecs_index archetype_id;
} entity_archetype_t; 

/**
 * @brief Creates an archetype for a given world.
 *
 * @param world The world the archetype is in.
 * @param component_count The number of components the archetype has.
 * @param components A pointer to the component ids the archetype has.
 * @param out_archetype The output archetype.
 */
void entity_archetype_create(struct ecs_world* world, u32 component_count, ecs_component_id* components, entity_archetype_t* out_archetype);
/**
 * @brief Creates an archetype from a base archetype and adds additional components.
 *
 * @param world The world the archetype is in.
 * @param base_archetype The base archetype.
 * @param component_count The number of new components.
 * @param components A pointer to an array of components to add.
 * @return A pointer to a new entity archetype owned by the ecs world.
 */
entity_archetype_t* entity_archetype_create_from_base(struct ecs_world* world, entity_archetype_t* base_archetype, u32 component_count, ecs_component_id* components);
/**
 * @brief Destroys an archetype and frees associated data.
 *
 * @param archetype The archetype to be freed.
 */
void entity_archetype_destroy(entity_archetype_t* archetype);
/**
 * @brief Prints debug information about an archetype.
 *
 * @param archetype The target entity.
 */
void entity_archetype_print_debug(entity_archetype_t* archetype);
/**
 * @brief Matches an archetype to existing queries in a world. This allows exising queries to iterate over newly created archetypes.
 *
 * @param archetyle The target archetype.
 * @param world The ecs world to match to.
 */
void entity_archetype_match_queryies(entity_archetype_t* archetyle, struct ecs_world* world);

darray_header(entity_archetype_t, entity_archetype);

// ================================
// ECS Component
// ================================
        /**
         * @class ecs_component
         * @brief Contains data about an archetype. Can be accessed via an ecs_component_id as the index.
         *
         */
typedef struct ecs_component {
    /**
     * @brief All archetypes that a componet is in.
     */
    darray_entity_archetype_ptr_t archetypes;
    /**
     * @brief Stride of the component in bytes.
     */
    u32 stride;
    /**
     * @brief Name of the component.
     */
    const char* name;
} ecs_component_t;
darray_header(ecs_component_t, ecs_component);

// ================================
// ECS iterator 
// ================================
        /**
         * @class ecs_iterator
         * @brief A container for all data required to iterate over all entities in an archetype.
         *
         */
typedef struct ecs_iterator {
    ecs_world_t* world;
    void** component_data;
    entity_archetype_t* archetype;
    u32 component_count;
    u32 entity_count;
} ecs_iterator_t;

#define ECS_ITERATOR_GET_COMPONENTS(iterator, index) (iterator->component_data[index]); SASSERT(index < iterator->component_count, "Cannot get component at index %d from query with %d components", index, iterator->component_count)
// void* ecs_iterator_get_type(ecs_iterator_t* iterator, ecs_component_id component);

// ================================
// ECS query 
// ================================
/**
 * @class ecs_query_create_info
 * @brief Contains all info required to create a query. Used by ecs_query and ecs_system
 *
 */
typedef struct ecs_query_create_info {
    u32 component_count;
    u32 without_component_count;
    const ecs_component_id* components;
    const ecs_component_id* without_components;
} ecs_query_create_info_t;

/**
 * @class ecs_query
 * @brief Used to match entity archetypes based on the components they do and don't have
 *
 */
typedef struct ecs_query {
    darray_u32_t archetype_indices;
    darray_u32_t components;
    darray_u32_t without_components;
    u32 hash;
    ecs_world_t* world;
} ecs_query_t;

darray_header(ecs_query_t, ecs_query);
#define MAX_QUERY_COMPONENT_COUNT 32

/**
 * @brief Creates an entity query for a given world based on the create info.
 *
 * @param world The ecs world the query belongs to.
 * @param create_info The information needed to build the query.
 * @return A pointer to the ecs query owned by the world.
 */
ecs_query_t* ecs_query_create(struct ecs_world* world, const ecs_query_create_info_t* create_info);
/**
 * @brief Destroys an ecs query.
 *
 * @param query The query to destroy.
 */
void ecs_query_destroy(ecs_query_t* query);
/**
 * @brief Checks if a query's requirements match the layout of an archetype
 *
 * @param query The source query.
 * @param archetype The archetype to be checked.
 * @return True if the query matches the archetype, false otherwise.
 */
b8 ecs_query_matches_archetype(ecs_query_t* query, entity_archetype_t* archetype);
/**
 * @brief Creates an iterator based on a query.
 *
 * @param query The source query.
 * @param out_iterator A pointer to the output iterator.
 */
void ecs_query_create_iterator(ecs_query_t* query, ecs_iterator_t* out_iterator);
/**
 * @brief Iterates over a query given an iterator.
 *
 * @param query The query to iterate over.
 * @param iterator The function that will for each entity archetype.
 */
void ecs_query_iterate(ecs_query_t* query, void (iterate_function)(ecs_iterator_t* iterator));

// ================================
// ECS system
// ================================
/**
 * @class ecs_system
 * @brief A container for a query and an iterate function. This will be automatically run when calling ecs_world_progress.
 *
 */
typedef struct ecs_system {
    ecs_query_t* query;
    void (*callback)(ecs_iterator_t* iterator);
#ifdef SPARK_DEBUG
    const char* name;
    f64 runtime;
    u32 calls;
#endif
} ecs_system_t;

/**
 * @brief Creates a system for a given world.
 *
 * @param world The world the system will run in.
 * @param phase The phase the system will execute in.
 * @param create_info The contraints to build the query.
 * @param callback The function that will be run for every archetype.
 * @param name The name of the system.
 */
void ecs_system_create(struct ecs_world* world, ecs_phase_t phase, const ecs_query_create_info_t* create_info, void (*callback)(ecs_iterator_t*), const char* name);
/**
 * @brief Destroys a system.
 *
 * @param system The system to be destroyed.
 */
void ecs_system_destroy(ecs_system_t* system);

darray_header(ecs_system_t, ecs_system);

// ================================
// Utility Macros
// ================================
#define ECS_COMPONENT_ID(component) ECS_##component##_ID
#define ECS_COMPONENT_DECLARE(component) ecs_component_id ECS_COMPONENT_ID(component)
#define ECS_SYSTEM_CREATE(world, phase, components, callback) ecs_system_create(world, phase, sizeof(components) / sizeof(ecs_component_id), callback, name)

