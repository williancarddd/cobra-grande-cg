#include "models.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>

std::vector<Triangle> cathedralModel, houseModel1, houseModel2, houseModel3, houseModel4, houseModel5;

void drawSTLModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotX, float rotY) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(scale, scale, scale);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glColor3f(0.82f, 0.71f, 0.55f); // Light brown color
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void drawModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotateX) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(scale, scale, scale);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza para as casas
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
        }
    }
    glEnd();
    glPopMatrix();
}
