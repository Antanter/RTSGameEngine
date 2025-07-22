#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;

    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<unsigned int>& indices);

    ~Mesh();

    void uploadToGPU();
    void draw() const;
};
