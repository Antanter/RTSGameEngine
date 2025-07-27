#include "RenderSystem.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Additionals.hpp"

void RenderSystem::Init() {
    camera.Init();
    window.Init();
}

void RenderSystem::BeginFrame() {
    SetClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderQueue.Clear();
}

void RenderSystem::CollectVisible() {
    AABB cameraBounds = camera.getWorldBounds();

}

void RenderSystem::RenderFrame() {
    BeginFrame();
    CollectVisible();
    SortAndBatch();
    Render();
    EndFrame();
}
