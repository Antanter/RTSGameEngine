#include "DrawBackend.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

OpenGLBackend::~OpenGLBackend() {
    delete shader;
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void OpenGLBackend::Init() {
    shader = new Shader("include/shaders/vertex.glsl", "include/shaders/fragment.glsl");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1); // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glEnableVertexAttribArray(2); // color
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLBackend::SetViewProjection(const glm::mat4 matrix) {
    viewProjMatrix = matrix;
}

void OpenGLBackend::DrawBatch(const RenderBatch& batch) {
    if (batch.vertices.empty()) return;

    shader->use();
    shader->setUniform("u_ViewProjection", viewProjMatrix);

    if (batch.texture) {
        batch.texture->Bind(0);
        shader->setUniform("u_Texture", 0);
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch.vertices.size() * sizeof(Vertex), batch.vertices.data());
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(batch.vertices.size()));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}