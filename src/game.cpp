#include <game.hpp>
#include <graphics/shapes/cube.hpp>
#include <physics/collision.hpp>
#include <scene/gameobject.hpp>

void Game::setupWindowEvents() {
    m_window.OnKeyPress = [&](int key) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                m_window.ToggleLockMouse();
                break;
        }
    };

    m_window.OnMouseMove = [&](double x, double y) {
        if (m_window.IsMouseLocked()) m_player.GetCamera().HandleMouseMovement(x, y);
    };

    m_window.ToggleLockMouse();
}

void Game::setupRendering() {
    m_shader = std::make_unique<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    m_mesh = std::make_unique<Mesh>(CreateCube());
}

void Game::Initialize() {
    setupWindowEvents();
    setupRendering();

    GameObject test{"Testing Object"};
    m_player.SetPosition({0.0f, 0.0f, 3.0f});

    m_staticColliders.push_back({
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3( 0.5f, 0.5f, 0.5f)
    });
}

void Game::Update(float deltatime) {
    m_player.HandleKeyboard(m_window.GetHandle(), deltatime);
    m_player.Update(deltatime);

    glm::vec3 pointOnSegment, pointOnBox;
    Capsule playerCapsule = m_player.GetCapsule();

    for (const auto& collider : m_staticColliders) {
        if (Collision::CapsulexAABB(playerCapsule, collider, pointOnSegment, pointOnBox)) {
            glm::vec3 diff = pointOnSegment - pointOnBox;
            float d = glm::length(diff);

            glm::vec3 dir = (d < 1e-6f) ? glm::vec3(0.0f, 1.0f, 0.0f) : (diff / d);

            float penDepth = playerCapsule.Radius - d;

            m_player.SetPosition(m_player.GetPosition() + (dir * penDepth));
            playerCapsule = m_player.GetCapsule();
        }
    }
}

void Game::Render() {
    m_shader->Bind();
        m_shader->SetMat4("uModel", glm::mat4{1.0f});
        m_shader->SetMat4("uView", m_player.GetCamera().GetViewMatrix());
        m_shader->SetMat4("uProjection", m_player.GetCamera().GetProjectionMatrix());

        m_mesh->Draw();
    m_shader->Unbind();
}
