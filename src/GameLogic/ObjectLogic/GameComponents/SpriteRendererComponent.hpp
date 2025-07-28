#pragma once
#include "IComponent.hpp"
#include <glm/glm.hpp>
#include "../../AnotherRendering/Texture.hpp"

class SpriteRendererComponent : public IComponent {
    private:
    Texture* texture;
    glm::vec4 color = glm::vec4(1.0f);
    glm::vec2 size = glm::vec2(1.0f);

    public:
    SpriteRendererComponent(Texture* texture) : texture(texture) {}

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

    void render(const glm::mat4& vp, const glm::mat4& modelMatrix) {
        texture->Bind();
        // нужно продумать как именно добавлять спрайт в рендер. возможно, придёться создать классс спрайта для удобства.
    }
};
