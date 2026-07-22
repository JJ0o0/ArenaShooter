#include <game.hpp>
#include <graphics/shapes/cube.hpp>
#include <physics/collision.hpp>
#include <scene/gameobject.hpp>

void Game::setupWindowEvents() {
    m_window.OnKeyPress = [&](int key) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                if (m_window.IsMouseLocked()) m_player.GetCamera().ResetMouseMovement();
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
    auto defaultShader = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    auto cube = std::make_shared<Mesh>(CreateCube());

    auto cubeModel = std::make_shared<Model>();
    cubeModel->Meshes = std::vector<std::shared_ptr<Mesh>>{cube};
    cubeModel->ModelShader = defaultShader;

    auto playerMaterial = std::make_shared<Material>();
    playerMaterial->Diffuse = glm::vec3(0.8f, 0.2f, 0.2f);
    playerMaterial->Specular = glm::vec3(0.3f);
    playerMaterial->Shininess = 16.0f;

    m_playerVisual.SetModel(cubeModel);
    m_playerVisual.SetMaterial(playerMaterial);

    GameObject floor{ "Floor" };

    auto floorMaterial = std::make_shared<Material>();
    floorMaterial->Diffuse = glm::vec3{0.18f, 0.20f, 0.16f};
    floorMaterial->Specular = glm::vec3{0.25f};
    floorMaterial->Shininess = 12.0f;

    floor.SetModel(cubeModel);
    floor.SetMaterial(floorMaterial);

    floor.GetTransform().Position = glm::vec3(0.0f, -0.5f, 0.0f);
    floor.GetTransform().Scale = glm::vec3(40.0f, 1.0f, 40.0f);
    floor.SetCollision(AABB{glm::vec3(-0.5f), glm::vec3(0.5f)});
    m_gameObjects.push_back(std::move(floor));

    m_light.Direction = glm::normalize(glm::vec3(-0.3f, -1.0f, -0.2f));
    m_light.Color = glm::vec3(1.0f, 0.95f, 0.85f);
    m_light.Ambient = glm::vec3(0.03f);
}

void Game::Initialize() {
    setupWindowEvents();
    setupRendering();

    m_player.SetPosition({0.0f, 3.0f, 3.0f});
}

void Game::Update(float deltatime) {
    m_player.HandleKeyboard(m_window.GetHandle(), deltatime);
    m_player.Update(deltatime);

    m_playerVisual.GetTransform() = m_player.GetVisualTransform();

    Capsule playerCapsule = m_player.GetCapsule();
    m_player.SetGrounded(false);
    for (const auto& obj : m_gameObjects) {
        CollisionShape worldShape = obj.GetWorldCollisionShape();

        const AABB* box = std::get_if<AABB>(&worldShape);
        if (!box) continue;

        glm::vec3 pointOnSegment, pointOnBox;
        if (Collision::CapsulexAABB(playerCapsule, *box, pointOnSegment, pointOnBox)) {
            glm::vec3 diff = pointOnSegment - pointOnBox;
            float d = glm::length(diff);

            glm::vec3 dir = (d < 1e-6f) ? glm::vec3(0.0f, 1.0f, 0.0f) : diff / d;
            float penDepth = playerCapsule.Radius - d;

            m_player.Translate(dir * penDepth);
            playerCapsule = m_player.GetCapsule();

            if (glm::dot(dir, glm::vec3(0.0f, 1.0f, 0.0f)) > 0.5f) {
                m_player.SetGrounded(true);

                glm::vec3 vel = m_player.GetVelocity();
                if (vel.y < 0.0f) {
                    vel.y = 0.0f;
                    m_player.SetVelocity(vel);
                }
            }
        }
    }
}

void Game::renderGameObject(const GameObject& obj) {
    const auto& material = obj.GetMaterial();
    const auto& model = obj.GetModel();
    const auto& shader = model->ModelShader;
    shader->Bind();
        glm::mat4 modelMatrix = obj.GetTransform().GetModel();
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        shader->SetMat3("uNormalMatrix", normalMatrix);
        shader->SetMat4("uModel", modelMatrix);
        shader->SetMat4("uView", m_player.GetCamera().GetViewMatrix());
        shader->SetMat4("uProjection", m_player.GetCamera().GetProjectionMatrix());
        shader->SetVec3("uViewPosition", m_player.GetCamera().Position);

        material->Apply(*shader);
        m_light.Apply(*shader);

        for (const auto& mesh : model->Meshes) mesh->Draw();
    shader->Unbind();
}

void Game::Render() {
    for (const auto& obj : m_gameObjects) {
        if (!obj.HasModel()) continue;

        renderGameObject(obj);
    }

    renderGameObject(m_playerVisual);
}
