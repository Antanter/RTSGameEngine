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

    RenderObject(Texture* tex, const glm::vec2& pos, const glm::vec2& scl, float rot, RenderLayer lay, float depth, const glm::vec4& col)
        : texture(tex), position(pos), scale(scl), rotation(rot), layer(lay), z(depth), color(col) {}
};
