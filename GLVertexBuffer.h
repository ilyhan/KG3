#pragma once

#include "Buffer.h"
#include <glad/glad.h>

class GLVertexBuffer : public Buffer {
public:
    GLVertexBuffer() : m_isCreated(false), m_isAlreadyDestroyed(false) {}
    virtual ~GLVertexBuffer() {
        if (m_isCreated) {
            destroy();
        }
    }

    bool isCreated() override {
        return m_isCreated;
    }

    void destroy() override {
        if (m_isCreated) {
            glDeleteBuffers(1, &m_VBO);
            glDeleteVertexArrays(1, &m_VAO);
            m_isCreated = false;
        }
    }

    void create() override {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        m_isCreated = true;
    }

    void bind() override {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void release() override {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void allocate(void* data, uint32_t size) override {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    bool m_isCreated;
    bool m_isAlreadyDestroyed;
};
