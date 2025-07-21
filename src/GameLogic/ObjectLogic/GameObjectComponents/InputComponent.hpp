#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IComponent.hpp"

struct InputComponent {

};

class InputAdapter : public IComponent {
    public:

    InputComponent data;

    InputAdapter(const InputComponent& tc) : data(tc) {}
    void render(const glm::mat4& vp) override {}
};