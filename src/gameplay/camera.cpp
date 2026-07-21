#include <gameplay/camera.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>

void Camera::HandleMouseMovement(double xpos, double ypos) {
    if (m_firstMouse) {
        m_lastMousePosition.x = xpos;
        m_lastMousePosition.y = ypos;
        m_firstMouse = false;
    }

    glm::vec2 offset{
        xpos - m_lastMousePosition.x,
        m_lastMousePosition.y - ypos,
    };

    m_lastMousePosition.x = xpos;
    m_lastMousePosition.y = ypos;

    offset *= m_properties.MouseSensitivity;

    m_yaw += offset.x;
    m_pitch += offset.y;
    m_pitch = std::clamp(m_pitch, m_properties.MinimumPitchClamp, m_properties.MaximumPitchClamp);

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
}

void Camera::SetAspectRatio(int width, int height) {
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

glm::vec3 Camera::GetRight() const { return glm::normalize(glm::cross(m_front, m_up)); }

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(
        Position,
        Position + m_front,
        m_up
    );
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return glm::perspective(
        glm::radians(m_properties.FieldOfView),
        m_aspectRatio,
        m_properties.NearPlane,
        m_properties.FarPlane
    );
};
