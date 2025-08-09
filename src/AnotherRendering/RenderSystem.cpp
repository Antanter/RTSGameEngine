#include "RenderSystem.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "Additionals.hpp"
#include "RenderObject.hpp"

void RenderSystem::Init() {
    window.Init();
    camera.Init();
}

void RenderSystem::SetScene(std::shared_ptr<Scene> scene) {
    currentScene = scene;
}

void RenderSystem::ExitWindow() {
    window.shouldClose();
}

void RenderSystem::BeginFrame() {
    SetClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::CollectVisible() {
    AABB cameraBounds = camera.getWorldBounds(window.getSize());

    if (auto scene = currentScene.lock()) {
        const std::vector<GameObject>& objects = scene->getObjects();

        for (const auto& objInfo : objects) {
            objInfo.
            if (renderable && renderable->IsVisible(cameraBounds)) {
                renderQueue.Add(renderable->CreateRenderObject());
            }
        }
    }

    for (const auto& chunk : objects) {
        for (const auto& tile : chunk.tiles) {
            if (tile.IsVisible()) {
                renderQueue.Add(CreateRenderObject(tile));
            }
        }
    }

    for (const auto& entity : world.GetEntities()) {
        if (entity.IsRenderable() && cameraBounds.Contains(entity.position)) {
            renderQueue.Add(CreateRenderObject(entity));
        }
    }

    for (const auto& uiElement : uiManager.GetElements()) {
        renderQueue.Add(CreateRenderObject(uiElement));
    }
}

void RenderSystem::SortAndBatch() {
    auto& items = renderQueue.GetItems();
    std::sort(items.begin(), items.end(), [](const RenderObject& a, const RenderObject& b) {
        if (a.layer != b.layer) return a.layer < b.layer;
        if (a.z != b.z) return a.z < b.z;
        return a.texture < b.texture;
    });

    for (const auto& item : items) {
        batcher.AddToBatch(item);
    }
}

void RenderSystem::Render() {
    drawBackend->SetViewProjection(camera.getViewProjection(window.getSize()));

    for (auto& layer : layerManager.GetSortedLayers()) {
        auto& batches = batcher.GetBatchesForLayer(layer);

        for (auto& batch : batches) {
            drawBackend->DrawBatch(batch);
        }
    }
}

void RenderSystem::EndFrame() {
    window.swapBuffers();

    renderQueue.Clear();
    batcher.Clear();
}

void RenderSystem::RenderFrame() {
    BeginFrame();
    CollectVisible();
    SortAndBatch();
    Render();
    EndFrame();
}
