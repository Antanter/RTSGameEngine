#pragma once

#include "RenderBatcher.hpp"

class DrawBackend {
    public:
    virtual void Init() = 0;
    virtual void DrawBatch(const RenderBatch& batch) = 0;
};

class OpenGLBackend : public DrawBackend {
    public:
    void Init() override;
    void DrawBatch(const RenderBatch& batch) override;
};
