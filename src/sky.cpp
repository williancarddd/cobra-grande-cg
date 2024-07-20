#include "sky.h"
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

void drawSky() {


    // Desenha a lua
    float moonRadius = 8.0f;
    float moonX = -70.0f, moonY = 30.0f, moonZ = -30.0f;

    glColor3f(0.8f, 0.8f, 0.8f); // Cor cinza clara para a lua
    glPushMatrix();
    glTranslatef(moonX, moonY, moonZ);
    glutSolidSphere(moonRadius, 20,20);
    glPopMatrix();

    // Desenha as estrelas
    glPointSize(2.0f); // Tamanho das estrelas
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para as estrelas

    for (int i = 0; i < 100; ++i) {
        float x = static_cast<float>(rand() % 200 - 100);
        float y = static_cast<float>(rand() % 200 - 100);
        float z = static_cast<float>(rand() % 200 - 100);
        glVertex3f(x, y, z);
    }

    glEnd();
}
