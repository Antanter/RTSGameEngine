#include "RenderQueue.hpp"

void RenderQueue::Add(const RenderObject& obj) {
    objects.push_back(obj);
}

void RenderQueue::Clear() {
    objects.clear();
}

std::vector<RenderObject>& RenderQueue::GetItems() {
    return objects;
}