#pragma once

#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <vector>
#include <memory>

struct Model {
    std::vector<std::shared_ptr<Mesh>> Meshes{};
    std::vector<std::unique_ptr<Shader>> Shaders{};
};
