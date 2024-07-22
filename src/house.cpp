#include "house.h"
#include "textures.h"
#include <GL/glut.h>

GLuint textureTopHome;
GLuint textureWall;
GLuint texturePortAndDoors;

void drawCube(float size) {
    float repeatFactor = 4.0f; // Factor to repeat the texture
    glBegin(GL_QUADS);
    // Frente
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(size, -size, size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(size, size, size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-size, size, size);
    // Trás
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(size, -size, -size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(size, size, -size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-size, size, -size);
    // Esquerda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(-size, -size, size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(-size, size, size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-size, size, -size);
    // Direita
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(size, -size, size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(size, size, size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(size, size, -size);
    // Topo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(size, size, size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(size, size, -size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-size, size, -size);
    // Fundo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(size, -size, size);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(size, -size, -size);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-size, -size, -size);
    glEnd();
}

void drawPyramid(float baseSize, float height) {
    float repeatFactor = 6.0f; // Factor to repeat the texture
    glBegin(GL_TRIANGLES);
    // Frente
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor / 2.0f, repeatFactor); glVertex3f(0.0f, height, 0.0f);
    // Trás
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, -baseSize);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(baseSize, 0.0f, -baseSize);
    glTexCoord2f(repeatFactor / 2.0f, repeatFactor); glVertex3f(0.0f, height, 0.0f);
    // Esquerda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, -baseSize);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor / 2.0f, repeatFactor); glVertex3f(0.0f, height, 0.0f);
    // Direita
    glTexCoord2f(0.0f, 0.0f); glVertex3f(baseSize, 0.0f, -baseSize);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor / 2.0f, repeatFactor); glVertex3f(0.0f, height, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    // Fundo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor, 0.0f); glVertex3f(baseSize, 0.0f, baseSize);
    glTexCoord2f(repeatFactor, repeatFactor); glVertex3f(baseSize, 0.0f, -baseSize);
    glTexCoord2f(0.0f, repeatFactor); glVertex3f(-baseSize, 0.0f, -baseSize);
    glEnd();
}

void drawHouse(int flag) {
    // Desenhar o corpo principal da casa
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawCube(2.5f);
    glPopMatrix();

    // Desenhar o telhado
    glBindTexture(GL_TEXTURE_2D, textureTopHome);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    drawPyramid(2.5f, 2.0f);
    glPopMatrix();

    // Desenhar a porta e as janelas com base na flag
    glBindTexture(GL_TEXTURE_2D, texturePortAndDoors);
    glColor3f(1.0f, 1.0f, 1.0f);
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
    glDisable(GL_TEXTURE_2D);
}
