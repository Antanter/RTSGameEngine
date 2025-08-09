#include "Additionals.hpp"

Color clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

void SetClearColor(const Color& color) {
    clearColor = color;
    glClearColor(color.r, color.g, color.b, color.a);
}
