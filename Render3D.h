#pragma once
#include "GLModel.h"

class Render3D
{
public:
    Render3D() = default;
    Render3D(GLModel* model, int _size);
    ~Render3D();

    void draw();
private:
    GLModel* object;
    int size;
};

Render3D::Render3D(GLModel* model, int _size) {
    object = model;
    size = _size;
}

void Render3D::draw() {
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr); 
}

Render3D::~Render3D() {

}
