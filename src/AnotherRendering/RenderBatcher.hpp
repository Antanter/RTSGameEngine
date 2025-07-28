#pragma once

#include <vector>
#include "Texture.hpp"
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
    void Clear();
    void AddToBatch(const RenderObject& obj);
    const std::vector<RenderBatch>& GetBatches() const;
    const std::vector<RenderBatch>& GetBatchesForLayer(RenderLayer) const;
};