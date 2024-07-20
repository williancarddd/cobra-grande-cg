#include "snake.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

Segment snake[MAX_SEGMENTS];
int numSegments = 50;
float segmentSize = 0.8f;
float snakeSpeed = 0.04f; // Ajuste para movimento suave
float radius = 5.0f; 
float elevationSpeed = 0.07f; // Ajuste para elevação suave
bool onSurface = false; // Flag para verificar se a cobra está na superfície
bool snakeDisappeared = false; // Flag para verificar se a cobra desapareceu
float boatX, boatY, boatZ; // Posição do barco

void initSnake() {
    for (int i = 0; i < numSegments; ++i) {
        snake[i].x = radius * cos(i * 2 * M_PI / numSegments);
        snake[i].y = -4.5f;
        snake[i].z = radius * sin(i * 2 * M_PI / numSegments);
        snake[i].r = 1.0f;
        snake[i].g = (i < numSegments / 2) ? (float)i / (numSegments / 2) : 1.0f;
        snake[i].b = 0.0f;
    }
}

void drawSnake() {
    if (snakeDisappeared) {
        return; // Não desenha a cobra se ela desapareceu
    }

    // Desenha a cabeça da cobra como um cubo
    glColor3f(snake[0].r, snake[0].g, snake[0].b);
    glPushMatrix();
    glTranslatef(snake[0].x, snake[0].y, snake[0].z);
    glutSolidCube(segmentSize);
    glPopMatrix();

    // Desenha o corpo da cobra
    for (int i = 1; i < numSegments - 1; ++i) {
        glColor3f(snake[i].r, snake[i].g, snake[i].b);
        glBegin(GL_QUADS);
        glVertex3f(snake[i].x, snake[i].y, snake[i].z);
        glVertex3f(snake[i].x, snake[i].y + segmentSize, snake[i].z);
        glVertex3f(snake[i + 1].x, snake[i + 1].y + segmentSize, snake[i + 1].z);
        glVertex3f(snake[i + 1].x, snake[i + 1].y, snake[i + 1].z);
        glEnd();
    }
}

void drawBoat(float x, float y, float z) {
    std::cout << "Desenhando barco em (" << x << ", " << y << ", " << z << ")" << std::endl; // Depuração
    // Desenha um barco simples na posição especificada
    glColor3f(0.3f, 0.2f, 0.1f); // Marrom para o barco
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(2.0f, 0.5f, 1.0f);
    glutSolidCube(segmentSize * 5); // Tamanho ajustado do barco
    glPopMatrix();
}

void updateSnake() {
    static float angle = 0.0f;
    static float totalAngle = 0.0f;
    angle += snakeSpeed;
    totalAngle += snakeSpeed;

    if (!onSurface) {
        // Elevação suave da cobra
        snake[0].x = radius * cos(angle);
        snake[0].y += elevationSpeed;
        snake[0].z = radius * sin(angle);

        if (snake[0].y >= 0.0f) {
            onSurface = true;
            for (int i = 0; i < numSegments; ++i) {
                snake[i].y = 0.0f; // Ajuste final da elevação
            }
        }
    } else if (totalAngle < 4 * M_PI) {
        // Cobra dá duas voltas ao redor do ponto inicial
        snake[0].x = radius * cos(angle);
        snake[0].z = radius * sin(angle);
    } else {
        // Cobra segue em linha reta
        snake[0].x -= 0.45;

        // Cobra atinge a posição x = -20 e desaparece
        if (snake[0].x <= -20.0f) {
            snakeDisappeared = true;
            boatX = snake[0].x;
            boatY = snake[0].y;
            boatZ = snake[0].z;
            std::cout << "Cobra desapareceu. Barco aparecerá em (" << boatX << ", " << boatY << ", " << boatZ << ")" << std::endl; // Depuração
        }
    }

    // Atualiza os segmentos da cobra
    for (int i = numSegments - 1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].z = snake[i - 1].z;
    }

    // Desenha o barco quando a cobra desaparece
    if (snakeDisappeared) {
        drawBoat(boatX, boatY, boatZ);
    }
}
