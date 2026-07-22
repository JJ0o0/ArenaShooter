#pragma once

#include <scene/transform.hpp>
#include <physics/shapes.hpp>
#include <scene/model.hpp>
#include <scene/uuid.hpp>
#include <string>

class GameObject {
    public:
        GameObject(const std::string& name);

        void SetName(const std::string& name) { m_name = name; }
        const std::string& GetName() const { return m_name; }

        bool HasModel() const { return m_model != nullptr; }
        void SetModel(const std::shared_ptr<Model>& model) { m_model = model; }
        const std::shared_ptr<Model>& GetModel() const { return m_model; }

        Transform& GetTransform() { return m_transform; }
        const Transform& GetTransform() const { return m_transform; }

        CollisionShape GetWorldCollisionShape() const;
        void SetCollision(const CollisionShape& shape) { m_collision = shape; }
        const CollisionShape& GetCollision() const { return m_collision; }

        const UUID& GetUUID() const { return m_uuid; }
    private:
        std::string m_name = "GameObject";
        UUID m_uuid{};

        std::shared_ptr<Model> m_model;

        Transform m_transform;
        CollisionShape m_collision;
};
