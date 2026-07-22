#include <scene/gameobject.hpp>
#include <utilities/overloaded.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <variant>

GameObject::GameObject(const std::string& name)
    : m_name(name) {
    std::cout << "Created '" << name << "' (uuid: '" << m_uuid.ToString() << "')\n";
}

CollisionShape GameObject::GetWorldCollisionShape() const {
    return std::visit(overloaded{
        [](std::monostate) -> CollisionShape {
            return std::monostate{};
        },
        [this](const AABB& box) -> CollisionShape {
            glm::vec3 worldMin = m_transform.Position + (box.Min * m_transform.Scale);
            glm::vec3 worldMax = m_transform.Position + (box.Max * m_transform.Scale);

            return AABB{worldMin, worldMax};
        },
        [this](const Sphere& s) -> CollisionShape {
            glm::vec3 worldCenter = m_transform.Position + (s.Center * m_transform.Scale);
            float worldRadius = s.Radius * glm::max(m_transform.Scale.x, m_transform.Scale.y, m_transform.Scale.z);

            return Sphere{worldCenter, worldRadius};
        },
        [this](const Capsule& c) -> CollisionShape {
            glm::vec3 aWorld = m_transform.Position + (c.A * m_transform.Scale);
            glm::vec3 bWorld = m_transform.Position + (c.B * m_transform.Scale);
            float worldRadius = c.Radius * glm::max(m_transform.Scale.x, m_transform.Scale.y, m_transform.Scale.z);

            return Capsule{aWorld, bWorld, worldRadius};
        }
    }, m_collision);
}
