#pragma once

#include <physics/shapes.hpp>
#include <graphics/mesh.hpp>
#include <scene/uuid.hpp>
#include <string>

class GameObject {
    public:
        GameObject(const std::string& name);

        void SetName(const std::string& name) { m_name = name; }
        const std::string& GetName() const { return m_name; }

        bool HasMesh() const { return m_mesh != nullptr; }
        void SetMesh(const std::shared_ptr<Mesh>& mesh) { m_mesh = mesh; }
        const std::shared_ptr<Mesh>& GetMesh() const { return m_mesh; }

        const UUID& GetUUID() const { return m_uuid; }
    private:
        std::string m_name = "GameObject";
        UUID m_uuid{};

        std::shared_ptr<Mesh> m_mesh;

        CollisionShape m_collision;
};
