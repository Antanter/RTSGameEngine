#include "RenderQueue.hpp"

void RenderQueue::Add(const RenderObject& obj) {
    objects.push_back(obj);
}

void RenderQueue::Clear() {
    objects.clear();
}

const std::vector<RenderObject>& RenderQueue::GetItems() const {
    return objects;
}