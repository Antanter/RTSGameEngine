#include "RenderSystem.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "GameLogic/ObjectLogic/GameComponents/TransformComponent.hpp"
#include "GameLogic/ObjectLogic/GameComponents/RendererComponent.hpp"
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

        for (const auto& object : objects) {
            const auto& render = object.getComponent<RendererComponent>();
            if (!render) continue;

            const auto& transform = object.getComponent<TransformComponent>();
            if (render && cameraBounds.contains(transform->position)) {
                RenderObject renderObject(render->texture, glm::vec2(transform->position), glm::vec2(transform->scale), 
                                            transform->rotation.z, render->layer, transform->position.z, render->color);
                renderQueue.Add(renderObject);
            }
        }
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
