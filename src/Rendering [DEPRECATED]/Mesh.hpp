#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    private:
    unsigned int VAO = 0, VBO = 0, EBO = 0;

    public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds)
        : vertices(verts), indices(inds) {}

    void uploadToGPU();
    void draw();
};
