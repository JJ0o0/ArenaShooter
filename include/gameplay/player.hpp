#pragma once

#include <gameplay/camera.hpp>
#include <physics/shapes.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct PlayerProperties {
    float Speed = 10.0f;
    float JumpForce = 5.0f;

    float Gravity = 20.0f;

    float Height = 1.8f;
    float Radius = 0.3f;

    float EyeHeight = 1.7f;
};

class Player {
    public:
        Player(const PlayerProperties& properties = {}) : m_properties(properties) {}

        void Update(float deltatime);
        void HandleKeyboard(GLFWwindow* glfwWindow, float deltatime);

        void Translate(const glm::vec3& target) { m_position += target; updateCamera(); }

        void SetGrounded(bool grounded) { m_grounded = grounded; }
        void SetPosition(const glm::vec3& position) { m_position = position; updateCamera(); }
        void SetVelocity(const glm::vec3& velocity) { m_velocity = velocity; }

        bool IsGrounded() const { return m_grounded; }
        const glm::vec3& GetPosition() const { return m_position; }
        const glm::vec3& GetVelocity() const { return m_velocity; }

        Capsule GetCapsule() const;

        Camera& GetCamera() { return m_camera; }
        const Camera& GetCamera() const { return m_camera; }
    private:
        PlayerProperties m_properties;

        bool m_grounded = false;

        glm::vec3 m_position{0.0f};
        glm::vec3 m_velocity{0.0f};

        Camera m_camera{};

        void updateCamera();
};
