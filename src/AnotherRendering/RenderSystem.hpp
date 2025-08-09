#pragma once

#include "RenderQueue.hpp"
#include "DrawBackend.hpp"
#include "LayerManager.hpp"
#include "Camera.hpp"
#include "Window.hpp"

#include "../GameLogic/SceneManagament/Scene.hpp"

#include <memory>

class RenderSystem {
    private:
    RenderQueue renderQueue;
    Batcher batcher;
    LayerManager layerManager;
    DrawBackend* drawBackend;
    std::weak_ptr<Scene> currentScene;

    Camera camera;
    Window window;

    public:
    RenderSystem();
    ~RenderSystem();

    void SetScene(std::shared_ptr<Scene> scene);
    void ExitWindow();

    void Init();
    void BeginFrame();
    void CollectVisible();
    void SortAndBatch();
    void Render();
    void EndFrame();

    void RenderFrame();
};