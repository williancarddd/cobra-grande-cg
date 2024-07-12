#include "environment.h"
#include "textures.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

std::vector<std::pair<float, float>> treePositions; // Definição da variável

void initTrees() {
    srand(static_cast<unsigned int>(time(NULL)));

    for (int i = 0; i < 50; ++i) { // Adiciona 50 posições de árvores
        float x = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(100.0f))); // Gera um valor entre -50.0f e 50.0f
        float z = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(100.0f))); // Gera um valor entre -50.0f e 50.0f
        treePositions.emplace_back(x, z);
    }
}

void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    float textureRepeat = 10.0f; // Ajustar para repetir a textura
    glBegin(GL_QUADS);
    for (float x = -100.0f; x < 100.0f; x += 2.0f) {
        for (float z = -100.0f; z < 100.0f; z += 2.0f) {
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x, 0.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, 0.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, 0.0f, z + 2.0f);
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x, 0.0f, z + 2.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawUnderground() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, underGroundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    float textureRepeat = 10.0f; // Ajustar para repetir a textura
    glBegin(GL_QUADS);
    for (float x = -100.0f; x < 100.0f; x += 2.0f) {
        for (float z = -100.0f; z < 100.0f; z += 2.0f) {
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x, -5.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, -5.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, -5.0f, z + 2.0f);
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x, -5.0f, z + 2.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


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

void drawSky() {
    glBegin(GL_QUADS);

    // Frente
    glColor3f(0.2f, 0.6f, 1.0f); // Azul claro no topo
    glVertex3f(-50.0f, 100.0f, -50.0f);
    glVertex3f(50.0f, 100.0f, -50.0f);
    glColor3f(0.8f, 0.9f, 1.0f); // Azul claro perto do horizonte
    glVertex3f(50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f, -50.0f);

    // Trás
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(50.0f, 100.0f, 50.0f);
    glVertex3f(-59.0f, 100.0f, 50.0f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(-50.0f, 0.0f, 50.0f);
    glVertex3f(50.0f, 0.0f, 50.0f);

     // Esquerda
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(50.0f, -100.0f, 50.0f);
    glVertex3f(-50.0f, -100.0f, 50.0f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(-100.0f, 0.0f, 50.0f);
    glVertex3f(50.0f, 0.0f, 50.0f);


    // Direita
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(-50.0f, -100.0f, -50.0f);
    glVertex3f(50.0f, -100.0f, -50.0f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(100.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f, -50.0f);
 
    // para ond a camera olha baixo
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(-50.0f, -100.0f, 50.0f);
    glVertex3f(-50.0f, -100.0f, -50.0f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f, 50.0f);

    // para ond a camera olha cima
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex3f(-50.0f, 100.0f, 50.0f);
    glVertex3f(-50.0f, 100.0f, -50.0f);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f, 50.0f);

    
    glEnd();
    
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 0.0f }; // Direção da luz do sol

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_position);
}
