#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "GLModel.h"
#include "Render3D.h"

using namespace std;

float pitch = 0.0f; // Вращение по оси X
float yaw = 0.0f;   // Вращение по оси Y
float scale = 1.0f; // Масштаб модели
float translateA = 0.0f;
bool mousePressed = false;
GLModel cube;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Управление вращением
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        pitch += 1.0f; // Вращение вверх
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        pitch -= 1.0f; // Вращение вниз
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        yaw -= 1.0f; // Вращение влево
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        yaw += 1.0f; // Вращение вправо
    }

    // Управление масштабом
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        scale += 0.003f; // Увеличение масштаба
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        scale -= 0.003f; // Уменьшение масштаба
        if (scale < 0.1f) scale = 0.1f; // Ограничение минимального масштаба
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        translateA += 0.02f; 
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        translateA -= 0.02f;
    }

}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1500, 1200, "OpenGL Cube", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Инициализация модели
    cube.initialize("Cube2.txt");

    // Создаем шейдер
    GLShader shader("VertexShader1.glsl", "PixelShader2.glsl");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Параметры камеры
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.01f, 10.0f);

        // Модельная матрица
        glm::mat4 model = glm::mat4(1.0f);
     
        model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale)); 
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, translateA));

        shader.bind();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::vec3 lightPos(2.0f, 2.0f, 2.0f);
        shader.setVec3("lightPos", lightPos);

        Render3D render(&cube, cube.getSize());
        render.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
