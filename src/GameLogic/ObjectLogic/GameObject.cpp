#include "GameObject.hpp"

void GameObject::update(float dt) {
    for (auto& [type, comp] : components)
        comp->update(dt);
}