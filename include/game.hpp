#pragma once

#include <platform/window.hpp>
#include <graphics/shader.hpp>
#include <graphics/mesh.hpp>
#include <gameplay/player.hpp>
#include <physics/shapes.hpp>
#include <memory>
#include <vector>

class Game {
    public:
        Game(Window& window) : m_window(window) {}

        void Initialize();
        void Update(float deltatime);
        void Render();
    private:
        Window& m_window;

        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Mesh> m_mesh;

        std::vector<AABB> m_staticColliders;

        Player m_player;

        void setupWindowEvents();
        void setupRendering();
};
