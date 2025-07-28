#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;
    glm::vec4 color;
};

struct Color {
    float r, g, b, a;
};

Color clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

void SetClearColor(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}