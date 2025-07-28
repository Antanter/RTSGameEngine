#pragma once

#include <glm/glm.hpp>
#include "Texture.hpp"
#include "Additionals.hpp"
#include "LayerManager.hpp"

struct RenderObject {
    Texture* texture;
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
    RenderLayer layer;
    float z;
    glm::vec4 color;
};
