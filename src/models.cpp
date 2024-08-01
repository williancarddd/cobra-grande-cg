#include "models.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>

std::vector<Triangle> cathedralModel, houseModel1, houseModel2, houseModel3, houseModel4, houseModel5, headModel, boatModel;

void setupMaterial() {
    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse[] = { 0.5f, 0.35f, 0.05f, 1.0f };
    GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // Reduced specular to reduce shine
    GLfloat mat_shininess[] = { 10.0f }; // Reduced shininess

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawSTLModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotX, float rotY, float rotZ) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(scale, scale, scale);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    setupMaterial(); // Call setupMaterial to set material properties
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
    glBegin(GL_TRIANGLES);
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
