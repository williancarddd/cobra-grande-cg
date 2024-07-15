#include "camera.h"
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

float cameraX = 35.0f, cameraY = -3.0f, cameraZ = 15.0f; // Inicia na posição inferior
float cameraAngleY = 0.0f, cameraDistance = 35.0f;
float cameraSpeed = 0.1f; // Velocidade de rotação da câmera
float cameraVerticalSpeed = 0.1f; // Velocidade de movimento vertical
bool movingUp = true; // Direção do movimento vertical

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        exit(0);
    } else if (key == '+') {
        cameraDistance -= 1.0f;
    } else if (key == '-') {
        cameraDistance += 1.0f;
    }
    glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y) {
    float angleSpeed = 2.0f;
    switch (key) {
    case GLUT_KEY_LEFT:
        cameraAngleY -= angleSpeed;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += angleSpeed;
        break;
    case GLUT_KEY_UP:
        cameraY += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 1.0f;
        break;
    }
    cameraX = cameraDistance * cos(cameraAngleY * M_PI / 180.0f);
    cameraZ = cameraDistance * sin(cameraAngleY * M_PI / 180.0f);
    glutPostRedisplay();
}

void updateCamera() {
    cameraAngleY += cameraSpeed;
    cameraX = cameraDistance * cos(cameraAngleY * M_PI / 180.0f);
    cameraZ = cameraDistance * sin(cameraAngleY * M_PI / 180.0f);

    if (movingUp) {
        cameraY += cameraVerticalSpeed;
        if (cameraY >= 20.0f) {
            movingUp = false;
        }
    } else {
        cameraY -= cameraVerticalSpeed;
        if (cameraY <= 5.0f) {
            movingUp = true;
        }
    }
}
