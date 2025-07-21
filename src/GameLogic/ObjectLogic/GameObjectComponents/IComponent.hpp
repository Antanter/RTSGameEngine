#pragma once

#include <glm/glm.hpp>

struct IComponent {
    virtual ~IComponent() = default;
    virtual void update(float dt) {}
    virtual void render(const glm::mat4& vp) {}
};