#include "Primitive.h"

Primitive::Primitive(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum mode)
    : vertices(vertices), indices(indices), drawMode(mode)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (!indices.empty()) {
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Element Buffer (if indices exist)
    if (!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    // Vertex Attributes (Position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Primitive::~Primitive()
{
    glDeleteBuffers(1, &VBO);
    if (!indices.empty()) {
        glDeleteBuffers(1, &EBO);
    }
    glDeleteVertexArrays(1, &VAO);
}


void Primitive::render() const {
    glBindVertexArray(VAO);
    if (!indices.empty()) {
        glDrawElements(drawMode, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(drawMode, 0, (GLsizei) vertices.size() / 3); // Assuming 3 components per vertex (x, y, z)
    }
    glBindVertexArray(0);
}

