#include "snake.h"
#include <GL/glut.h>
#include <math.h>

Segment snake[MAX_SEGMENTS];
int numSegments = 100;
float segmentSize = 1.0f;
float snakeSpeed = 0.02f; 
float radius = 5.0f; 
float elevationSpeed = 0.1f; // Velocidade de elevação

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
    for (int i = 0; i < numSegments - 1; ++i) {
        glColor3f(snake[i].r, snake[i].g, snake[i].b);
        glBegin(GL_QUADS);
        glVertex3f(snake[i].x, snake[i].y, snake[i].z);
        glVertex3f(snake[i].x, snake[i].y + segmentSize, snake[i].z);
        glVertex3f(snake[i + 1].x, snake[i + 1].y + segmentSize, snake[i + 1].z);
        glVertex3f(snake[i + 1].x, snake[i + 1].y, snake[i + 1].z);
        glEnd();
    }
}

void updateSnake() {
    static float angle = 0.0f;
    angle += snakeSpeed;

    for (int i = numSegments - 1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].z = snake[i - 1].z;
    }

    snake[0].x = radius * cos(angle);
    snake[0].y += elevationSpeed; // Faz a cobra subir gradualmente
    snake[0].z = radius * sin(angle);

    if (snake[0].y > 0.0f) {
        for (int i = 0; i < numSegments; ++i) {
            snake[i].y = 0.0f; // Limita a elevação para que a cobra não saia da superfície
        }
    }
}