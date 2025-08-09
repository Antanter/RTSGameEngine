#pragma once

#include "Services.hpp"
#include <glm/glm.hpp>

struct IComponent {
    virtual ~IComponent() = default;
    virtual void update() {}
};