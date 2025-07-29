#pragma once

#include "RenderBatcher.hpp"
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

    Camera& camera;
    Window window;

    public:
    RenderSystem();
    ~RenderSystem();

    void LoadSceneToRender(std::shared_ptr<Scene> scene);

    void Init();
    void BeginFrame();
    void CollectVisible();
    void SortAndBatch();
    void Render();
    void EndFrame();

    void RenderFrame();
};