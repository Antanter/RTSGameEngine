#pragma once
#include "IComponent.hpp"
#include <memory>

class ScriptComponent : public IComponent {
    private:
    std::unique_ptr<IComponent> script;

    public:
    ScriptComponent(std::unique_ptr<IComponent> script)
        : script(std::move(script)) {}

    void update(float dt) override {
        script->update(dt);
    }

    void render(const glm::mat4& vp) override {
        script->render(vp);
    }
};
