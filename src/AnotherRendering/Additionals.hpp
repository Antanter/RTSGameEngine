#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;
    glm::vec4 color;
};

struct Color {
    float r, g, b, a;
};

extern Color clearColor;

void SetClearColor(const Color& color);
