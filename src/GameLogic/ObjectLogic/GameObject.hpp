#pragma once

#include "GameComponents/IComponent.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <unordered_map>
#include <typeindex>

class GameObject {
    private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components;

    public:
    template<typename T, typename... Args> T* addComponent(Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->setOwner(this);
        T* ptr = comp.get();
        components[typeid(T)] = std::move(comp);
        return ptr;
    }

    template<typename T> T* getComponent() const {
        auto it = components.find(typeid(T));
        if (it != components.end())
            return dynamic_cast<T*>(it->second.get());
        return nullptr;
    }

    void update() {}
};