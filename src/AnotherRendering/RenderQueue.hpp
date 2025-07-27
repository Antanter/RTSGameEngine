#pragma once
#include <vector>
#include "RenderObject.hpp"

class RenderQueue {
    private:
    std::vector<RenderObject> objects;

    public:
    void Clear();
    void Add(const RenderObject& obj);
    const std::vector<RenderObject>& GetItems() const;
};
