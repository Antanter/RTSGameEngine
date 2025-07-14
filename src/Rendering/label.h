//
// Created by Andrii Klykavka on 14.07.2025.
//

#ifndef LABEL_H
#define LABEL_H

#pragma once
#include <string>
#include <glm/glm.hpp>

class Label {
public:
    std::string text;
    float x, y, scale;
    glm::vec3 color;

    Label(std::string text, float x, float y, float scale, glm::vec3 color)
        : text(text), x(x), y(y), scale(scale), color(color) {}
};

#endif //LABEL_H
