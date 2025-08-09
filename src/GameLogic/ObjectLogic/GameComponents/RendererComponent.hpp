#pragma once
#include "IComponent.hpp"
#include <glm/glm.hpp>
#include "../../../AnotherRendering/Texture.hpp"
#include "../../../AnotherRendering/LayerManager.hpp"

struct RendererComponent : public IComponent {
    Texture* texture;
    RenderLayer layer;
    glm::vec4 color = glm::vec4(1.0f);

    RendererComponent(Texture* texture) : texture(texture) {}

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }
};

class RendererAdapter : public IComponent {
    public:
    RendererComponent data;
    RendererAdapter(const RendererComponent& tc) : data(tc) {}
};