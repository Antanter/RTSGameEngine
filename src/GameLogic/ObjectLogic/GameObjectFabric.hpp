#pragma once
#include "GameObject.hpp"
#include "TransformComponent.hpp"
//#include "MeshRendererComponent.hpp"
//#include "ScriptComponent.hpp"

class GameObjectBuilder {
    private:

    std::unique_ptr<GameObject> obj;

    public:

    GameObjectBuilder() {
        obj = std::make_unique<GameObject>();
    }

    GameObjectBuilder& withTransform(const glm::vec3& position = glm::vec3(0.0f),
                                     const glm::vec3& rotation = glm::vec3(0.0f),
                                     const glm::vec3& scale = glm::vec3(1.0f)) {
        TransformComponent tc;
        tc.position = position;
        tc.rotation = rotation;
        tc.scale = scale;
        obj->addComponent<TransformAdapter>(tc);
        return *this;
    }

    template<typename T, typename... Args>
    GameObjectBuilder& withComponent(Args&&... args) {
        obj->addComponent<T>(std::forward<Args>(args)...);
        return *this;
    }

    std::unique_ptr<GameObject> build() {
        return std::move(obj);
    }
};