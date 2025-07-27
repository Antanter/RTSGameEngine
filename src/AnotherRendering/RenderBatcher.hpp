#pragma once
#include <vector>
#include "RenderObject.hpp"

struct RenderBatch {
    Texture* texture;
    std::vector<Vertex> vertices;
};

class Batcher {
    private:
    std::vector<RenderBatch> batches;

    public:
    void Batch(const std::vector<RenderObject>& objects);
    const std::vector<RenderBatch>& GetBatches() const;
};