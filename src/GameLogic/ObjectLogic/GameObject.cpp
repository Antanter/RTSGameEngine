#include "GameObject.hpp"

void GameObject::update() {
    for (auto& [type, comp] : components) {
        comp->update();
    }
}