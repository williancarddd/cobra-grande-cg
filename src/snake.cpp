#include "snake.h"
#include <GL/glut.h>
#include <math.h>

Segment snake[MAX_SEGMENTS];
int numSegments = 100;
float segmentSize = 1.0f;
float snakeSpeed = 0.2f;
float amplitude = 1.2f;
float frequency = 0.5f;

void initSnake() {
    for (int i = 0; i < numSegments; ++i) {
        snake[i].x = i * segmentSize;
        snake[i].y = -4.5f;
        snake[i].z = 0.0f;
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
    static float t = 0.0f;
    t += snakeSpeed;
    float newX = snake[0].x - snakeSpeed;
    float newZ = amplitude * sin(frequency * newX);

    for (int i = numSegments - 1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].z = snake[i - 1].z;
    }

    snake[0].x = newX;
    snake[0].y = -4.5f;
    snake[0].z = newZ;

    if (snake[0].x < -10.0f) {
        for (int i = 0; i < numSegments; ++i) {
            snake[i].x += 20.0f;
        }
    }
    if (snake[0].x > 10.0f) {
        for (int i = 0; i < numSegments; ++i) {
            snake[i].x -= 20.0f;
        }
    }
}
