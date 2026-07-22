#pragma once

#include <graphics/shader.hpp>
#include <glm/glm.hpp>

struct Material {
    glm::vec3 Diffuse{1.0f};
    glm::vec3 Specular{1.0f};
    float Shininess = 16.0f;

    virtual ~Material() = default;

    virtual void Apply(Shader& shader) {
        shader.SetVec3("uMaterial.Diffuse", Diffuse);
        shader.SetVec3("uMaterial.Specular", Specular);
        shader.SetFloat("uMaterial.Shininess", Shininess);
    }
};
