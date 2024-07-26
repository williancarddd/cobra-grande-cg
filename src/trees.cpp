// src/trees.cpp
#include "trees.h"
#include "environment.h"
#include <GL/glut.h>
#include <textures.h>
void drawTrees() {
    glPushMatrix();

    for (const auto& position : treePositions) {
        float x = position.first;
        float z = position.second;

        glPushMatrix();
        glTranslatef(x, 0.0f, z);

        // Desenhar o tronco
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, trunkTexture);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        glRotatef(-90, 1.0, 0.0, 0.0);
        gluCylinder(quad, 0.2, 0.2, 2.0, 32, 32); // Tronco: raio base, raio topo, altura, slices, stacks
        gluDeleteQuadric(quad);
        glDisable(GL_TEXTURE_2D);

        // Desenhar a copa
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, foliageTexture);
        glTranslatef(0.0f, 0.0f, 2.0f); // Mover para o topo do tronco
        glutSolidSphere(1.0, 32, 32); // Copa: raio, slices, stacks
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }

    glPopMatrix();
}
