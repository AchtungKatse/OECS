#include "OECS/ecs/ecs.h"
#include "OECS/ecs/ecs_world.h"

// Rendering
ECS_COMPONENT_DECLARE(camera_t);
ECS_COMPONENT_DECLARE(mesh_t);
ECS_COMPONENT_DECLARE(material_t);

// Culling
ECS_COMPONENT_DECLARE(aabb_t);

// Transforms
ECS_COMPONENT_DECLARE(dirty_transform_t);
ECS_COMPONENT_DECLARE(translation_t);
ECS_COMPONENT_DECLARE(rotation_t);
ECS_COMPONENT_DECLARE(scale_t);
ECS_COMPONENT_DECLARE(local_to_world_t);

ECS_COMPONENT_DECLARE(translation_2d_t);
ECS_COMPONENT_DECLARE(scale_2d_t);
// ECS_COMPONENT_DECLARE(local_to_world_2d_t);

ECS_COMPONENT_DECLARE(entity_parent_t);
ECS_COMPONENT_DECLARE(entity_child_t);

// Physics
ECS_COMPONENT_DECLARE(physics_body_t);
ECS_COMPONENT_DECLARE(velocity_t);

void ecs_register_types(ecs_world_t* world) {
}
