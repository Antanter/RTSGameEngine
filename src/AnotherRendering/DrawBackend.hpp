#pragma once

#include "RenderBatcher.hpp"
#include "Shaders.hpp"

class DrawBackend {
    public:
    virtual ~DrawBackend();
    virtual void Init() = 0;
    virtual void SetViewProjection(const glm::mat4) = 0;
    virtual void DrawBatch(const RenderBatch&) = 0;
};

class OpenGLBackend : public DrawBackend {
    private:
    Shader* shader = nullptr;
    glm::mat4 viewProjMatrix;
    GLuint vao = 0;
    GLuint vbo = 0;

    public:
    ~OpenGLBackend() override;
    void Init() override;
    void SetViewProjection(const glm::mat4) = 0;
    void DrawBatch(const RenderBatch&) override;
};
