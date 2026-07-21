#include <gameplay/player.hpp>

void Player::Update(float deltatime) {
    m_position += m_velocity * deltatime;

    updateCamera();
}

void Player::HandleKeyboard(GLFWwindow* glfwWindow, float deltatime) {
    glm::vec3 forward = m_camera.GetFront();
    forward = glm::normalize(forward);

    glm::vec3 right = m_camera.GetRight();
    right.y = 0.0f;
    right = glm::normalize(right);

    glm::vec3 direction{0.0f};

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS) direction += forward;
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS) direction -= forward;
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS) direction += right;
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS) direction -= right;

    bool isMoving = glm::length(direction) > 0.0f;
    if (isMoving) direction = glm::normalize(direction);

    float speed = isMoving ? m_properties.Speed : 0.0f;

    m_velocity.x = direction.x * speed;
    m_velocity.z = direction.z * speed;
}

Capsule Player::GetCapsule() const {
    Capsule c{};
    c.A = m_position + glm::vec3{0.0f, m_properties.Radius, 0.0f};
    c.B = m_position + glm::vec3{0.0f, m_properties.Height - m_properties.Radius, 0.0f};
    c.Radius = m_properties.Radius;

    return c;
}

void Player::updateCamera() {
    m_camera.Position = m_position + glm::vec3(0.0f, m_properties.EyeHeight, 0.0f);
}
