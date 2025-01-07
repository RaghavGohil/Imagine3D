#pragma once
#include <string> 
#include <glad/glad.h>
#include <vector>

class Primitive {
private:
    unsigned int VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    GLenum drawMode; // GL_TRIANGLES, GL_LINES, etc.

public:
    Primitive(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum mode = GL_TRIANGLES);
    ~Primitive();
    void render() const;
};