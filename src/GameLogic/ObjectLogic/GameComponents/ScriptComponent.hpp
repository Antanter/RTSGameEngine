#pragma once
#include "IComponent.hpp"
#include <memory>

class ScriptComponent : public IComponent {
    private:
    std::unique_ptr<IComponent> script;

    public:
    ScriptComponent(std::unique_ptr<IComponent> script) : script(std::move(script)) {}

    void update() override {
        script->update();
    }
};
