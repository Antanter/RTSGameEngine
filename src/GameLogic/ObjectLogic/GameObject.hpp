#pragma once

#include "IComponent.hpp"

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

class GameObject {
    private:
    
    std::vector<std::unique_ptr<IComponent>> components;

    public:

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit IComponent");
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = ptr.get();
        components.push_back(std::move(ptr));
        return raw;
    }

    template<typename T>
    T* getComponent() {
        for (auto& c : components) {
            if (auto ptr = dynamic_cast<T*>(c.get()))
                return ptr;
        }
        return nullptr;
    }

    void update(float dt) {
        for (auto& c : components) c->update(dt);
    }

    void render(const glm::mat4& vp) {
        for (auto& c : components) c->render(vp);
    }
};
