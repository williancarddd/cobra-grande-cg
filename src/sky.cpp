// src/sky.cpp
#include "sky.h"
#include <GL/glut.h>

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