#include <scene/gameobject.hpp>
#include <iostream>

GameObject::GameObject(const std::string& name)
    : m_name(name) {
    std::cout << "Created '" << name << "' (uuid: '" << m_uuid.ToString() << "')\n";
}
