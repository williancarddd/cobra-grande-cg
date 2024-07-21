#include "house.h"
#include <GL/glut.h>

void drawCube(float size) {
    glBegin(GL_QUADS);
    // Frente
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    // Trás
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    // Esquerda
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    // Direita
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    // Topo
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    // Fundo
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glEnd();
}

void drawPyramid(float baseSize, float height) {
    glBegin(GL_TRIANGLES);
    // Frente
    glVertex3f(-baseSize, 0.0f, baseSize);
    glVertex3f(baseSize, 0.0f, baseSize);
    glVertex3f(0.0f, height, 0.0f);
    // Trás
    glVertex3f(-baseSize, 0.0f, -baseSize);
    glVertex3f(baseSize, 0.0f, -baseSize);
    glVertex3f(0.0f, height, 0.0f);
    // Esquerda
    glVertex3f(-baseSize, 0.0f, -baseSize);
    glVertex3f(-baseSize, 0.0f, baseSize);
    glVertex3f(0.0f, height, 0.0f);
    // Direita
    glVertex3f(baseSize, 0.0f, -baseSize);
    glVertex3f(baseSize, 0.0f, baseSize);
    glVertex3f(0.0f, height, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    // Fundo
    glVertex3f(-baseSize, 0.0f, baseSize);
    glVertex3f(baseSize, 0.0f, baseSize);
    glVertex3f(baseSize, 0.0f, -baseSize);
    glVertex3f(-baseSize, 0.0f, -baseSize);
    glEnd();
}

void drawHouse(int flag) {
    // Desenhar o corpo principal da casa
    glColor3f(0.79f, 0.85f, 0.59f);
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawCube(2.5f);
    glPopMatrix();

    // Desenhar o telhado
    glColor3f(0.31f, 0.33f, 0.47f);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    drawPyramid(2.5f, 2.0f);
    glPopMatrix();

    // Desenhar a porta e as janelas com base na flag
    glColor3f(0.29f, 0.57f, 0.75f); // Cor da porta e janelas
    switch (flag) {
        case 1: // Frente
            // Porta
            glPushMatrix();
            glTranslatef(0.0f, 1.0f, 2.51f);
            glScalef(1.0f, 2.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela esquerda
            glPushMatrix();
            glTranslatef(-1.0f, 2.5f, 2.51f);
            glScalef(1.0f, 1.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela direita
            glPushMatrix();
            glTranslatef(1.0f, 2.5f, 2.51f);
            glScalef(1.0f, 1.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            break;
        case 2: // Trás
            // Porta
            glPushMatrix();
            glTranslatef(0.0f, 1.0f, -2.51f);
            glScalef(1.0f, 2.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela esquerda
            glPushMatrix();
            glTranslatef(-1.0f, 2.5f, -2.51f);
            glScalef(1.0f, 1.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela direita
            glPushMatrix();
            glTranslatef(1.0f, 2.5f, -2.51f);
            glScalef(1.0f, 1.0f, 0.1f);
            drawCube(0.5f);
            glPopMatrix();
            break;
        case 3: // Esquerda
            // Porta
            glPushMatrix();
            glTranslatef(-2.51f, 1.0f, 0.0f);
            glScalef(0.1f, 2.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela esquerda
            glPushMatrix();
            glTranslatef(-2.51f, 2.5f, -1.0f);
            glScalef(0.1f, 1.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela direita
            glPushMatrix();
            glTranslatef(-2.51f, 2.5f, 1.0f);
            glScalef(0.1f, 1.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            break;
        case 4: // Direita
            // Porta
            glPushMatrix();
            glTranslatef(2.51f, 1.0f, 0.0f);
            glScalef(0.1f, 2.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela esquerda
            glPushMatrix();
            glTranslatef(2.51f, 2.5f, -1.0f);
            glScalef(0.1f, 1.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            // Janela direita
            glPushMatrix();
            glTranslatef(2.51f, 2.5f, 1.0f);
            glScalef(0.1f, 1.0f, 1.0f);
            drawCube(0.5f);
            glPopMatrix();
            break;
    }
}