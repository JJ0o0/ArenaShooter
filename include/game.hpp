#pragma once

#include <platform/window.hpp>
#include <scene/gameobject.hpp>
#include <gameplay/player.hpp>
#include <graphics/light.hpp>
#include <physics/shapes.hpp>
#include <vector>

class Game {
    public:
        Game(Window& window) : m_window(window) {}

        void Initialize();
        void Update(float deltatime);
        void Render();
    private:
        Window& m_window;

        std::vector<GameObject> m_gameObjects;

        Player m_player;
        Light m_light;

        void setupWindowEvents();
        void setupRendering();
};
