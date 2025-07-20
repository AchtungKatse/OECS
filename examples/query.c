/**
 * @file
 * @brief Examples on how to create and iterate over queries. \code{.c}
#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct name {
    const char* value;
} name_t;

typedef struct employee {
    const int id;
} employee_t;

typedef struct salary {
    int value;
} salary_t;

typedef struct technician {
    float years_experience;
} technician_t;

typedef struct manager {
    float years_experience;
} manager_t;

typedef struct employee_fired {
    int date;
} employee_fired_t;

ECS_COMPONENT_DECLARE(name_t); 
ECS_COMPONENT_DECLARE(employee_t); 
ECS_COMPONENT_DECLARE(salary_t); 
ECS_COMPONENT_DECLARE(technician_t); 
ECS_COMPONENT_DECLARE(manager_t); 
ECS_COMPONENT_DECLARE(employee_fired_t); 

// Utility function
entity_t add_employee(ecs_world_t* world, const char* name, int id, int salary);

// All iterators for the example queries
void iterate_employees(ecs_iterator_t* iterator);
void iterate_managers(ecs_iterator_t* iterator);
void iterate_active_employees(ecs_iterator_t* iterator);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, name_t);
    ECS_COMPONENT_DEFINE(world, employee_t);
    ECS_COMPONENT_DEFINE(world, salary_t);
    ECS_COMPONENT_DEFINE(world, technician_t);
    ECS_COMPONENT_DEFINE(world, manager_t);
    ECS_COMPONENT_DEFINE(world, employee_fired_t);

    // Create employees
    entity_t paul = add_employee(world, "Paul", 0, 80000);
    ENTITY_SET_COMPONENT(world, paul, manager_t, { 3.2f });

    entity_t mike = add_employee(world, "Mike", 1, 70000);
    ENTITY_SET_COMPONENT(world, mike, manager_t, { 1.1f });
    ENTITY_SET_COMPONENT(world, mike, technician_t, { 5.0f });

    entity_t james = add_employee(world, "James", 2, 55000);
    ENTITY_SET_COMPONENT(world, james, technician_t, { 1.0f });

    entity_t sam = add_employee(world, "Sam", 3, 45000);
    ENTITY_SET_COMPONENT(world, sam, technician_t, { 0.1f });
    ENTITY_SET_COMPONENT(world, sam, employee_fired_t, { 42 });

    entity_t sabrina = add_employee(world, "Sabrina", 4, 65000);
    ENTITY_SET_COMPONENT(world, sabrina, technician_t, { 2.0f });

    entity_t sofia = add_employee(world, "Sofia", 5, 51000);
    ENTITY_SET_COMPONENT(world, sofia, technician_t, { 0.8f });


    // query over all employees
    ecs_query_create_info_t employee_query_create = {
        .component_count = 3,
        .components = (ecs_component_id[]) {
            ECS_COMPONENT_ID(name_t),
            ECS_COMPONENT_ID(employee_t),
            ECS_COMPONENT_ID(salary_t),
        }
    };
    ecs_query_t* employee_query = ecs_query_create(world, &employee_query_create);

    // Query over only managers
    ecs_query_create_info_t manager_query_create = {
        .component_count = 2,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(name_t),
            ECS_COMPONENT_ID(manager_t),
        }
    };
    ecs_query_t* manager_query = ecs_query_create(world, &manager_query_create);

    // Query over active employees
    // NOTE: This only matches entities without the employeed_fired_t component
    ecs_query_create_info_t active_employee_query_create = {
        .component_count = 1,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(name_t),
        },
        .without_component_count = 1,
        .without_components = (ecs_component_id[1]) { 
            ECS_COMPONENT_ID(employee_fired_t),
        }
    };
    ecs_query_t* active_employee_query = ecs_query_create(world, &active_employee_query_create);

    // Queries have now been created, but must be iterated to act on the entities they matched
    SINFO("Iterating over employees");
    ecs_query_iterate(employee_query, iterate_employees);

    SINFO("");
    SINFO("Iterating over managers");
    ecs_query_iterate(manager_query, iterate_managers);

    SINFO("");
    SINFO("Iterating over only active employees");
    ecs_query_iterate(active_employee_query, iterate_active_employees);

    // Shutdown world
    ecs_world_shutdown(world);
}

entity_t add_employee(ecs_world_t* world, const char* name, int id, int salary) {
    entity_t employee = entity_create(world);

    ENTITY_SET_COMPONENT(world, employee, name_t, { .value = name});
    ENTITY_SET_COMPONENT(world, employee, employee_t, { .id = id});
    ENTITY_SET_COMPONENT(world, employee, salary_t, { .value = salary});

    return employee;
}

void iterate_employees(ecs_iterator_t* iterator) {
    // Get the arrays of each component
    // This will be in the same order as their query_create_info structure
    // i.e. The employee query defined components in the order
    // 0: ECS_COMPONENT_ID(name_t),
    // 1: ECS_COMPONENT_ID(employee_t),
    // 2: ECS_COMPONENT_ID(salary_t),
    // So the component index will match that order
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    const employee_t* employees = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);
    const salary_t* salaries = ECS_ITERATOR_GET_COMPONENTS(iterator, 2);

    // Then iterate over each entity
    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tName:   %s:", names[i].value);
        SINFO("\tID:     %d:", employees[i].id);
        SINFO("\tSalary: %d:", salaries[i].value);
        SINFO("");
    }
}
void iterate_managers(ecs_iterator_t* iterator) {
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    const manager_t* managers = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);

    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tManager %s has %f years of experience", names[i].value, managers[i].years_experience);
    }
}

void iterate_active_employees(ecs_iterator_t* iterator) {
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);

    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tEmployee %s is an active employee.", names[i].value);
    }
}
 * \endcode
 */

#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"
#include "OECS/ecs/entity.h"

// Declare components
typedef struct name {
    const char* value;
} name_t;

typedef struct employee {
    const int id;
} employee_t;

typedef struct salary {
    int value;
} salary_t;

typedef struct technician {
    float years_experience;
} technician_t;

typedef struct manager {
    float years_experience;
} manager_t;

typedef struct employee_fired {
    int date;
} employee_fired_t;

ECS_COMPONENT_DECLARE(name_t); 
ECS_COMPONENT_DECLARE(employee_t); 
ECS_COMPONENT_DECLARE(salary_t); 
ECS_COMPONENT_DECLARE(technician_t); 
ECS_COMPONENT_DECLARE(manager_t); 
ECS_COMPONENT_DECLARE(employee_fired_t); 

// Utility function
entity_t add_employee(ecs_world_t* world, const char* name, int id, int salary);

// All iterators for the example queries
void iterate_employees(ecs_iterator_t* iterator);
void iterate_managers(ecs_iterator_t* iterator);
void iterate_active_employees(ecs_iterator_t* iterator);

int main(int argc, char** argv) {
    // Create world
    ecs_world_t* world = ecs_world_initialize();

    // Define components
    ECS_COMPONENT_DEFINE(world, name_t);
    ECS_COMPONENT_DEFINE(world, employee_t);
    ECS_COMPONENT_DEFINE(world, salary_t);
    ECS_COMPONENT_DEFINE(world, technician_t);
    ECS_COMPONENT_DEFINE(world, manager_t);
    ECS_COMPONENT_DEFINE(world, employee_fired_t);

    // Create employees
    entity_t paul = add_employee(world, "Paul", 0, 80000);
    ENTITY_SET_COMPONENT(world, paul, manager_t, { 3.2f });

    entity_t mike = add_employee(world, "Mike", 1, 70000);
    ENTITY_SET_COMPONENT(world, mike, manager_t, { 1.1f });
    ENTITY_SET_COMPONENT(world, mike, technician_t, { 5.0f });

    entity_t james = add_employee(world, "James", 2, 55000);
    ENTITY_SET_COMPONENT(world, james, technician_t, { 1.0f });

    entity_t sam = add_employee(world, "Sam", 3, 45000);
    ENTITY_SET_COMPONENT(world, sam, technician_t, { 0.1f });
    ENTITY_SET_COMPONENT(world, sam, employee_fired_t, { 42 });

    entity_t sabrina = add_employee(world, "Sabrina", 4, 65000);
    ENTITY_SET_COMPONENT(world, sabrina, technician_t, { 2.0f });

    entity_t sofia = add_employee(world, "Sofia", 5, 51000);
    ENTITY_SET_COMPONENT(world, sofia, technician_t, { 0.8f });


    // query over all employees
    ecs_query_create_info_t employee_query_create = {
        .component_count = 3,
        .components = (ecs_component_id[]) {
            ECS_COMPONENT_ID(name_t),
            ECS_COMPONENT_ID(employee_t),
            ECS_COMPONENT_ID(salary_t),
        }
    };
    ecs_query_t* employee_query = ecs_query_create(world, &employee_query_create);

    // Query over only managers
    ecs_query_create_info_t manager_query_create = {
        .component_count = 2,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(name_t),
            ECS_COMPONENT_ID(manager_t),
        }
    };
    ecs_query_t* manager_query = ecs_query_create(world, &manager_query_create);

    // Query over active employees
    // NOTE: This only matches entities without the employeed_fired_t component
    ecs_query_create_info_t active_employee_query_create = {
        .component_count = 1,
        .components = (ecs_component_id[]) { 
            ECS_COMPONENT_ID(name_t),
        },
        .without_component_count = 1,
        .without_components = (ecs_component_id[1]) { 
            ECS_COMPONENT_ID(employee_fired_t),
        }
    };
    ecs_query_t* active_employee_query = ecs_query_create(world, &active_employee_query_create);

    // Queries have now been created, but must be iterated to act on the entities they matched
    SINFO("Iterating over employees");
    ecs_query_iterate(employee_query, iterate_employees);

    SINFO("");
    SINFO("Iterating over managers");
    ecs_query_iterate(manager_query, iterate_managers);

    SINFO("");
    SINFO("Iterating over only active employees");
    ecs_query_iterate(active_employee_query, iterate_active_employees);

    // Shutdown world
    ecs_world_shutdown(world);
}

entity_t add_employee(ecs_world_t* world, const char* name, int id, int salary) {
    entity_t employee = entity_create(world);

    ENTITY_SET_COMPONENT(world, employee, name_t, { .value = name});
    ENTITY_SET_COMPONENT(world, employee, employee_t, { .id = id});
    ENTITY_SET_COMPONENT(world, employee, salary_t, { .value = salary});

    return employee;
}

void iterate_employees(ecs_iterator_t* iterator) {
    // Get the arrays of each component
    // This will be in the same order as their query_create_info structure
    // i.e. The employee query defined components in the order
    // 0: ECS_COMPONENT_ID(name_t),
    // 1: ECS_COMPONENT_ID(employee_t),
    // 2: ECS_COMPONENT_ID(salary_t),
    // So the component index will match that order
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    const employee_t* employees = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);
    const salary_t* salaries = ECS_ITERATOR_GET_COMPONENTS(iterator, 2);

    // Then iterate over each entity
    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tName:   %s:", names[i].value);
        SINFO("\tID:     %d:", employees[i].id);
        SINFO("\tSalary: %d:", salaries[i].value);
        SINFO("");
    }
}
void iterate_managers(ecs_iterator_t* iterator) {
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);
    const manager_t* managers = ECS_ITERATOR_GET_COMPONENTS(iterator, 1);

    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tManager %s has %f years of experience", names[i].value, managers[i].years_experience);
    }
}

void iterate_active_employees(ecs_iterator_t* iterator) {
    const name_t* names = ECS_ITERATOR_GET_COMPONENTS(iterator, 0);

    for (int i = 0; i < iterator->entity_count; i++) {
        SINFO("\tEmployee %s is an active employee.", names[i].value);
    }
}
