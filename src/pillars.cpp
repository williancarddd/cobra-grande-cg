// src/pillars.cpp
#include "pillars.h"
#include <GL/glut.h>

void drawPillars() {
    float pillarHeight = 5.0f;
    float pillarWidth = 0.5f;
    glColor3f(0.22f, 0.22f, 0.22f);
    for (float x = -100.0f; x <= 100.0f; x += 10.0f) {
        for (float z = -100.0f; z <= 100.0f; z += 10.0f) {
            glPushMatrix();
            glTranslatef(x, -pillarHeight / 2, z);
            glBegin(GL_QUADS);
            // Front face
            glVertex3f(-pillarWidth / 2, -pillarHeight / 2, pillarWidth / 2);
            glVertex3f(pillarWidth / 2, -pillarHeight / 2, pillarWidth / 2);
            glVertex3f(pillarWidth / 2, pillarHeight / 2, pillarWidth / 2);
            glVertex3f(-pillarWidth / 2, pillarHeight / 2, pillarWidth / 2);
            // Back face
            glVertex3f(-pillarWidth / 2, -pillarHeight / 2, -pillarWidth / 2);
            glVertex3f(pillarWidth / 2, -pillarHeight / 2, -pillarWidth / 2);
            glVertex3f(pillarWidth / 2, pillarHeight / 2, -pillarWidth / 2);
            glVertex3f(-pillarWidth / 2, pillarHeight / 2, -pillarWidth / 2);
            // Left face
            glVertex3f(-pillarWidth / 2, -pillarHeight / 2, -pillarWidth / 2);
            glVertex3f(-pillarWidth / 2, -pillarHeight / 2, pillarWidth / 2);
            glVertex3f(-pillarWidth / 2, pillarHeight / 2, pillarWidth / 2);
            glVertex3f(-pillarWidth / 2, pillarHeight / 2, -pillarWidth / 2);
            // Right face
            glVertex3f(pillarWidth / 2, -pillarHeight / 2, -pillarWidth / 2);
            glVertex3f(pillarWidth / 2, -pillarHeight / 2, pillarWidth / 2);
            glVertex3f(pillarWidth / 2, pillarHeight / 2, pillarWidth / 2);
            glVertex3f(pillarWidth / 2, pillarHeight / 2, -pillarWidth / 2);
            glEnd();
            glPopMatrix();
        }
    }
}
