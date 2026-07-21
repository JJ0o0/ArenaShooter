#pragma once

#include <glm/glm.hpp>
#include <variant>

struct AABB {
    glm::vec3 Min{0.0f};
    glm::vec3 Max{1.0f};
};

struct Capsule {
    glm::vec3 A{0.0f};
    glm::vec3 B{1.0f};
    float Radius = 1.0f;
};

struct Sphere {
    glm::vec3 Center{0.0f};
    float Radius = 1.0f;
};

using CollisionShape = std::variant<
    std::monostate,
    AABB,
    Sphere,
    Capsule
>;
