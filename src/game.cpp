#include <game.hpp>
#include <graphics/shapes/cube.hpp>

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
}

void Game::Update(float deltatime) {
    m_player.HandleKeyboard(m_window.GetHandle(), deltatime);
    m_player.Update(deltatime);
}

void Game::Render() {
    m_shader->Bind();
        m_shader->SetMat4("uModel", glm::mat4{1.0f});
        m_shader->SetMat4("uView", m_player.GetCamera().GetViewMatrix());
        m_shader->SetMat4("uProjection", m_player.GetCamera().GetProjectionMatrix());

        m_mesh->Draw();
    m_shader->Unbind();
}
