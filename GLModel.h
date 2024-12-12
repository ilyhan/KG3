#pragma once

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLShader.h"
#include "Loader.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "VertexData.h"

class GLModel {
public:
    GLModel() = default;
    ~GLModel();

    void initialize(std::string filename);
    int getSize();

private:
    GLShader* m_modelShaderProgram = nullptr;

    std::vector<VertexData> m_vertices = {};
    std::vector<int> m_indices = {};

    GLIndexBuffer m_indexBuffer;
    GLVertexBuffer m_vertexBuffer;
};

GLModel::~GLModel() {
}

int GLModel::getSize() {
    return m_indices.size();
}

void GLModel::initialize(std::string filename) {
    Loader load;
    load.LoadObjModel(filename, m_vertices, m_indices);

    m_vertexBuffer.create(); // Create the vertex buffer
    m_vertexBuffer.bind(); // Bind the vertex buffer
    m_vertexBuffer.allocate(m_vertices.data(), m_vertices.size() * sizeof(VertexData)); // Allocate vertex data

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal)); // ”казатель на нормали
    glEnableVertexAttribArray(2);

    m_indexBuffer.create(); // Create the index buffer
    m_indexBuffer.bind(); // Bind the index buffer
    m_indexBuffer.allocate(m_indices.data(), m_indices.size() * sizeof(unsigned int)); // Allocate index data
}