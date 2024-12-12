#pragma once

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLShader.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct VertexData {
    float position[3];
    float color[3];
    float normal[3]; // Добавлено поле для нормалей
};

class GLModel {
public:
    GLModel() = default;
    GLModel(std::vector<VertexData> vertices, std::vector<int> indices);
    ~GLModel();

    void draw();
    void initialize();

private:
    GLShader* m_modelShaderProgram = nullptr;

    std::vector<VertexData> m_vertices = {
        {{1.0f, -1.0f, -1.0f}, {0.3f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // Vertex 1
        {{1.0f, -1.0f,  1.0f}, {0.7f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // Vertex 2
        {{-1.0f, -1.0f,  1.0f}, {0.6f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, // Vertex 3
        {{-1.0f, -1.0f, -1.0f}, {0.3f, 0.3f, 0.3f}, {0.0f, -1.0f, 0.0f}}, // Vertex 4
        {{1.0f,  1.0f, -1.0f}, {0.3f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // Vertex 5
        {{1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // Vertex 6
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // Vertex 7
        {{-1.0f,  1.0f, -1.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}  // Vertex 8
    };

    std::vector<int> m_indices = {
        4, 0, 3, // Triangle 1
        4, 3, 7, // Triangle 2
        2, 6, 7, // Triangle 3
        2, 7, 3, // Triangle 4
        1, 5, 2, // Triangle 5
        5, 6, 2, // Triangle 6
        0, 4, 1, // Triangle 7
        4, 5, 1, // Triangle 8
        4, 7, 5, // Triangle 9
        7, 6, 5, // Triangle 10
        0, 1, 2, // Triangle 11
        0, 2, 3  // Triangle 12
    };

    GLIndexBuffer m_indexBuffer;
    GLVertexBuffer m_vertexBuffer;
};

#include "GLModel.h"

GLModel::GLModel(std::vector<VertexData> vertices, std::vector<int> indices) {
    m_vertices = vertices;
    m_indices = indices;
    initialize();
}

GLModel::~GLModel() {
    // Resource cleanup is handled in GLIndexBuffer and GLVertexBuffer destructors
}

void GLModel::initialize() {
    m_vertexBuffer.create(); // Create the vertex buffer
    m_vertexBuffer.bind(); // Bind the vertex buffer
    m_vertexBuffer.allocate(m_vertices.data(), m_vertices.size() * sizeof(VertexData)); // Allocate vertex data

    // Установка указателей на атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal)); // Указатель на нормали
    glEnableVertexAttribArray(2);


    m_indexBuffer.create(); // Create the index buffer
    m_indexBuffer.bind(); // Bind the index buffer
    m_indexBuffer.allocate(m_indices.data(), m_indices.size() * sizeof(unsigned int)); // Allocate index data
}

void GLModel::draw() {
    m_vertexBuffer.bind(); // Bind the vertex buffer
    m_indexBuffer.bind(); // Bind the index buffer

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr); // Draw the model
}
