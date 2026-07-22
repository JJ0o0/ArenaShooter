#pragma once

#include <graphics/shader.hpp>
#include <glm/glm.hpp>

struct Light {
    glm::vec3 Color{1.0f};
    glm::vec3 Ambient{0.1f};
    glm::vec3 Direction{0.0f, -1.0f, 0.0f};

    virtual ~Light() = default;

    virtual void Apply(Shader& shader) {
        shader.SetVec3("uLight.Color", Color);
        shader.SetVec3("uLight.Ambient", Ambient);
        shader.SetVec3("uLight.Direction", Direction);
    }
};
