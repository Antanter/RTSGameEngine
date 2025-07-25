#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IComponent.hpp"

struct TransformComponent {
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};

    glm::mat4 getModelMatrix() const {
        glm::mat4 t = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1,0,0));
        glm::mat4 rY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0,1,0));
        glm::mat4 rZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0,0,1));
        glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);
        return t * (rZ * rY * rX) * s;
    }
};

class TransformAdapter : public IComponent {
    public:

    TransformComponent data;

    TransformAdapter(const TransformComponent& tc) : data(tc) {}
};