#pragma once
#include <memory>
#include "GameObject.hpp"
#include "TransformComponent.hpp"

class GameObjectBuilder {
    private:
    std::unique_ptr<GameObject> obj;

    public:
    GameObjectBuilder() {}

    template<typename T, typename... Args>
    GameObjectBuilder& withComponent(Args&&... args) {
        obj->addComponent<T>(std::forward<Args>(args)...);
        return *this;
    }

    std::unique_ptr<GameObject> build() {
        return std::move(obj);
    }
};
