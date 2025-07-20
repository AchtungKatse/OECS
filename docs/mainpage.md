\mainpage OECS Documentation

\section intro_sec Overview

OECS is an open source entity component system designed to allow for better utilization of system resources and faster development times.

\section core_sec Core Concepts

In contrast to standard object oriented design using inheritance, OECS separates the data for its objects into components which can be accessed via an entity id and operated on by a system.
OECS stoers all of this data in a world which handles how all data is stored and managed.

\section quickstart_sec Examples
\ref examples/components.c \n
\ref examples/systems.c \n
\ref examples/entities.c \n
\ref examples/query.c \n

\section quickstart_sec Quickstart
\subsection world_create Step 1: Creating a world
As mentioned above, all ecs data is stored in a world which must be created at the start of the program to function.
This can be done using the \ref ecs_world_initialize function.

i.e. 
\code{.c}
 ecs_world_t* world = ecs_world_initialize();
\endcode

Once the world is created, every entity and component created will be relative to the world.

\subsection create_comp_sec Step 2: Creating Components
Components are used to store all data for an object. It is recommended to separate components into the most atomic level possible for better code reuse to maximize the cache hit rate.
\n For example, a generic entity in c++ using may have a layout such as
\code{.c++}
class Node {
 public:
     const char* name;
};
\endcode
and would later be inherited from to create new objects.
\code{.c++} 
class Node3D : Node {
 public:
     Vector3 position;
};
\endcode

This creates a node with both a name and position. \n In contrast, best practices for an ECS are to have two unique components that will later be referenced by an entity to access the data.
\nI.e.
\code{.c}
typedef struct node_name {
 const char* name;
} node_name_t;

typedef struct position {
 vec3 value;
} position_t;
\endcode

To create a component in OECS, it needs to have its data defined by a struct then declared and defined. For components to function, they need to be assigned a unique id that can be used to lookup their
respective data. Furthermore, user code will need to access this id which requires it to be defined in a header. An example of how to create a component can be seen below.
\code{.c}
typedef struct counter {
     int count;
} counter_t;

// Note: this may need to be prefixed by extern if shared across multiple files. See component.h for more information
ECS_COMPONENT_DECLARE(counter_t);

int main(int argc, char** argv) {
 ...

 ECS_COMPONENT_DEFINE(world, counter_t);
}
\endcode

see \ref examples/components.c for more information.
*
\subsection entity_create_sec Step 3: Creating an entity
Entities are created using the \ref entity_create function.
\code{.c}
entity_t entity = entity_create(world);
\endcode

Entities can then add, remove, or get components with the following macros:
\code{.c}
ENTITY_ADD_COMPONENT(world, entity, counter_t);
ENTITY_SET_COMPONENT(world, entity, counter_t, { .count = 5 });
counter_t* counter = ENTITY_GET_COMPONENT(world, entity, counter_t);
\endcode

\subsection system_create_sec Step 4: Creating a system
Systems will match to all entities with a specific query and iterate over them in a specific \ref ecs_phase automatically when calling \ref ecs_world_progress.
Systems will need an associated \ref query_create_info to create their respective query

\code{.c}
void increment_counters(ecs_iterator_t* iterator) {
     counter_t* counters = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
     for (int i = 0; i < iterator->entity_count; i++) {
         counters[i].count += 1;
     }
 }

...

query_create_info query_info = {
  .component_count = 1,
  .components = (ecs_component_id*) { ECS_COMPONENT_ID(counter_t), },
 };
 ecs_system_create(world, ECS_PHASE_UPDATE, query_info, increment_counters, "increment_system");

 ecs_world_progress(world);
\endcode
The above code will create a system that matches any entity with a counter_t component. When \ref ecs_world_progress is called, the increment_counter function is called with a matching iterator. 
The function then gets the counter array from the entities and iterates over each one, adding 1 to the counter.
For more information on creating systems, see \ref examples/systems.c.

\subsection complete_example_sec Complete Example Code
\code{.c}
void increment_counters(ecs_iterator_t* iterator) {
     counter_t* counters = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
     for (int i = 0; i < iterator->entity_count; i++) {
         counters[i].count += 1;
     }
 }

typedef struct counter {
     int count;
} counter_t;

// Note: this may need to be prefixed by extern if shared across multiple files. See component.h for more information
ECS_COMPONENT_DECLARE(counter_t);

int main(int argc, char** argv) {
     ecs_world_t* world = ecs_world_initialize();

     ECS_COMPONENT_DEFINE(world, counter_t);

     entity_t entity = entity_create(world);
     ENTITY_SET_COMPONENT(world, entity, counter_t, { .count = 5 });

     query_create_info query_info = {
         .component_count = 1,
         .components = (ecs_component_id*) { ECS_COMPONENT_ID(counter_t), },
     };
     ecs_system_create(world, ECS_PHASE_UPDATE, query_info, increment_counters, "increment_system");

     ecs_world_progress(world);
}

\endcode





