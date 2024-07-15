// src/trees.cpp
#include "trees.h"
#include "environment.h"
#include <GL/glut.h>

void drawTrees() {
    glColor3f(0.4f, 0.2f, 0.0f); // Cor marrom para o tronco

    for (const auto& position : treePositions) {
        float x = position.first;
        float z = position.second;

        glPushMatrix();
        glTranslatef(x, 0.0f, z);

        // Desenhar o tronco
        GLUquadric* quad = gluNewQuadric();
        glRotatef(-90, 1.0, 0.0, 0.0);
        glColor3f(0.4f, 0.2f, 0.0f); // Cor marrom para o tronco
        gluCylinder(quad, 0.2, 0.2, 2.0, 32, 32); // Tronco: raio base, raio topo, altura, slices, stacks
        gluDeleteQuadric(quad);

        // Desenhar a copa
        glTranslatef(0.0f, 0.0f, 2.0f); // Mover para o topo do tronco
        glColor3f(0.0f, 0.5f, 0.0f); // Cor verde para a copa
        glutSolidSphere(1.0, 32, 32); // Copa: raio, slices, stacks

        glPopMatrix();
    }
}
