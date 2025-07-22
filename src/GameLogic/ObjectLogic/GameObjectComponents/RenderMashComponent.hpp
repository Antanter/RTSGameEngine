#pragma once
#include "IComponent.hpp"
#include <glm/glm.hpp>

class MeshRendererComponent : public IComponent {
    private:
    Mesh mesh;
    Material material;
    TransformAdapter* meshTransform = nullptr;

    public:
    MeshRendererComponent(const Mesh& mesh, const Material& material)
        : mesh(mesh), material(material) {}

    void render(const glm::mat4& vp) override {
        material.use();
        material.shader.setMat4("viewProj", vp);
        material.shader.setMat4("model", meshTransform->getModelMatrix());
        mesh.draw();
    }

    void MeshRendererAdapter(MeshRendererAdapter* adapter) {
        meshTransform = adapter;
    }
};
