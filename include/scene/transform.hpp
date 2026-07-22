#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Transform {
    glm::vec3 Position{0.0f};
    glm::quat Rotation = glm::identity<glm::quat>();
    glm::vec3 Scale{1.0f};

    void SetEulerAngles(const glm::vec3& degrees) { Rotation = glm::quat(glm::radians(degrees)); }
    glm::vec3 GetEulerAngles() const { return glm::degrees(glm::eulerAngles(Rotation)); }

    glm::mat4 GetModel() const {
        glm::mat4 model{1.0f};
        model = glm::translate(model, Position);
        model *= glm::toMat4(Rotation);
        model = glm::scale(model, Scale);

        return model;
    };
};
