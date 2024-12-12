#pragma once

#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

class GLShader : public Shader {
public:
    GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    virtual ~GLShader();

    void bind() const override;
    void release() const override;
    void setInt(const std::string& name, int value) override;
    void setIntArray(const std::string& name, int* values, uint32_t count) override;
    void setFloat(const std::string& name, float value) override;
    void setVec2(const std::string& name, const glm::vec2& value) override;
    void setVec3(const std::string& name, const glm::vec3& value) override;
    void setVec4(const std::string& name, const glm::vec4& value) override;
    void setMat3(const std::string& name, const glm::mat3& matrix) override;
    void setMat4(const std::string& name, const glm::mat4& matrix) override;
    unsigned int m_shaderId;

private:

    bool isCompiledShaders(const std::string& vertexSource, const std::string& fragmentSource);
    bool isShaderProgramCompiledSuccess(const unsigned int shader, const ShaderType& shaderType);
};

GLShader::GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::ifstream vertexFile(vertexShaderPath);
    std::ifstream fragmentFile(fragmentShaderPath);

    std::stringstream vertexStream, fragmentStream;
    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    std::string vertexSource = vertexStream.str();
    std::string fragmentSource = fragmentStream.str();

    m_shaderId = glCreateProgram();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSourceCStr = vertexSource.c_str(); // Преобразование в const char*
    glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr); // Передаем указатель на указатель
    glCompileShader(vertexShader);
    glAttachShader(m_shaderId, vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceCStr = fragmentSource.c_str(); // Преобразование в const char*
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr); // Передаем указатель на указатель
    glCompileShader(fragmentShader);
    glAttachShader(m_shaderId, fragmentShader);

    glLinkProgram(m_shaderId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


GLShader::~GLShader() {
    glDeleteProgram(m_shaderId);
}

void GLShader::bind() const {
    glUseProgram(m_shaderId);
}

void GLShader::release() const {
    glUseProgram(0);
}

void GLShader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void GLShader::setIntArray(const std::string& name, int* values, uint32_t count) {
    glUniform1iv(glGetUniformLocation(m_shaderId, name.c_str()), count, values);
}

void GLShader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(m_shaderId, name.c_str()), value);
}

void GLShader::setVec2(const std::string& name, const glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setVec3(const std::string& name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setVec4(const std::string& name, const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
}

void GLShader::setMat3(const std::string& name, const glm::mat3& matrix) {
    glUniformMatrix3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void GLShader::setMat4(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}