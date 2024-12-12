//// GLModel.cpp
//#include "GLModel.h"
//
//GLModel::GLModel(const std::vector<VertexData>& vertices, const std::vector<int>& indices) :
//    m_vertices(vertices),
//    m_indices(indices)
//{
//    initialize();
//}
//
//GLModel::~GLModel()
//{
//    if (m_indexBuffer.isCreated())
//        m_indexBuffer.destroy();
//    if (m_vertexBuffer.isCreated())
//        m_vertexBuffer.destroy();
//    delete m_modelShaderProgram; // Properly delete the shader program to prevent memory leaks
//}
//
//void GLModel::draw()
//{
//    m_modelShaderProgram->bind();
//
//    m_vertexBuffer.bind();
//    m_modelShaderProgram->enableAttributeArray(0); // Enable vertex position attribute
//    m_modelShaderProgram->setAttributeBuffer(0, 3, GL_FLOAT, sizeof(VertexData), (void*)offsetof(VertexData, position));
//
//    m_modelShaderProgram->enableAttributeArray(1); // Enable color attribute
//    m_modelShaderProgram->setAttributeBuffer(1, 3, GL_FLOAT, sizeof(VertexData), (void*)offsetof(VertexData, color));
//
//    m_indexBuffer.bind();
//    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
//
//    m_indexBuffer.release();
//    m_modelShaderProgram->disableAttributeArray(0); // Disable vertex position attribute
//    m_modelShaderProgram->disableAttributeArray(1); // Disable color attribute
//    m_vertexBuffer.release();
//    m_modelShaderProgram->release();
//}
//
//void GLModel::initialize()
//{
//    // Create vertex buffer
//    m_vertexBuffer.bind();
//    m_vertexBuffer.allocate(m_vertices.data(), m_vertices.size() * sizeof(VertexData));
//    m_vertexBuffer.release();
//
//    // Create index buffer
//    m_indexBuffer.bind();
//    m_indexBuffer.allocate(m_indices.data(), m_indices.size() * sizeof(int));
//    m_indexBuffer.release();
//
//    // Load shader
//    m_modelShaderProgram = new GLShader("model.vs", "model.fs");
//}
