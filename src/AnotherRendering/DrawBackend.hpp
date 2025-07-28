#pragma once

#include "RenderBatcher.hpp"

class DrawBackend {
    public:
    virtual void Init() = 0;
    virtual void SetViewProjection(const glm::mat4) = 0;
    virtual void DrawBatch(const RenderBatch&) = 0;
};

class OpenGLBackend : public DrawBackend {
    public:
    void Init() override;
    void SetViewProjection(const glm::mat4) = 0;
    void DrawBatch(const RenderBatch&) override;
};
