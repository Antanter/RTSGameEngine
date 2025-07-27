#pragma once

#include "RenderBatcher.hpp"
#include "RenderQueue.hpp"
#include "DrawBackend.hpp"
#include "LayerManager.hpp"
#include "Camera.hpp"
#include "Window.hpp"

class RenderSystem {
    private:
    RenderQueue renderQueue;
    Batcher batcher;
    LayerManager layerManager;
    DrawBackend* drawBackend;

    Camera& camera;
    Window window;

    public:
    RenderSystem();
    ~RenderSystem();

    void Init();
    void BeginFrame();
    void CollectVisible();
    void SortAndBatch();
    void Render();
    void EndFrame();

    void RenderFrame();
};
