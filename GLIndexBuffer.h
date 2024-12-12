#pragma once

#include "Buffer.h"
#include <glad/glad.h>

class GLIndexBuffer : public Buffer {
public:
    GLIndexBuffer() : m_isCreated(false), m_isAlreadyDestroyed(false) {}
    virtual ~GLIndexBuffer() {
        if (m_isCreated) {
            destroy();
        }
    }

    bool isCreated() override {
        return m_isCreated;
    }

    void destroy() override {
        if (m_isCreated) {
            glDeleteBuffers(1, &m_indexBufferId);
            m_isCreated = false;
        }
    }

    void create() override {
        glGenBuffers(1, &m_indexBufferId);
        m_isCreated = true;
    }

    void bind() override {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    }

    void release() override {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void allocate(void* data, uint32_t size) override {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

private:
    unsigned int m_indexBufferId;
    bool m_isCreated;
    bool m_isAlreadyDestroyed;
};
