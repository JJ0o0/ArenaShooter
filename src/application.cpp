#include <application.hpp>
#include <platform/system_info.hpp>
#include <game.hpp>
#include <glad/gl.h>

int Application::Run() {
    m_window = std::make_unique<Window>();

    WindowProperties windowProps {
        .Title = "Arena Shooter",
        .Width = 800,
        .Height = 600,
        .VSync = true,
        .Resizable = false,
    };

    if (!m_window->Initialize(windowProps)) return -1;

    SystemInfo::Initialize();

    Game game{*m_window};
    game.Initialize();

    float lastTime = glfwGetTime();
    while (!m_window->ShouldClose()) {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        deltaTime = std::min(deltaTime, 0.05f);

        m_window->PollEvents();
        game.Update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        game.Render();
        m_window->SwapBuffers();
    }

    m_window->Destroy();
    return 0;
}
