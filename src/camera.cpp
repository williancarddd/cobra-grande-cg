#include "camera.h"
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

float cameraX = 35.0f, cameraY = 10.0f, cameraZ = 15.0f;
float cameraAngleY = 0.0f, cameraDistance = 35.0f;

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
    cameraX = 35.0f * cos(cameraAngleY * M_PI / 180.0f);
    cameraZ = 35.0f * sin(cameraAngleY * M_PI / 180.0f);
    glutPostRedisplay();
}
