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
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
            // degrade de cores
            glColor3f(0.5f + 0.5f * (i % 3), 0.5f + 0.5f * (i % 3), 0.5f + 0.5f * (i % 3));
            
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
    glBegin(GL_TRIANGLES);
    // cor marrom
    glColor3f(0.5f, 0.35f, 0.05f);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
        }
    }
    glEnd();
    glPopMatrix();
}
