#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

class GameObject {
    protected:

    glm::vec2 position;
    glm::vec2 size;
    float rotation = 0.0f;
    
    public:

    virtual ~GameObject() {}

    virtual void update(float deltaTime) = 0;
    virtual void render(const glm::mat4& projection) = 0;

    glm::vec2 getPosition() const { return position; }
    void setPosition(glm::vec2 pos) { position = pos; }
};
