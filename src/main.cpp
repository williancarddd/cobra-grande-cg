#include <GL/glut.h>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include "snake.h"
#include "textures.h"
#include "stl_loader.h"
#include "models.h"
#include "camera.h"
#include "audio.h"
#include "environment.h"
#include "lighting.h"
#include "sky.h"
#include "ground.h"
#include "underground.h"
#include "pillars.h"
#include "trees.h"
#include "lake.h"
#include "house.h"

#define M_PI 3.14159265358979323846

// Variável para controlar o início da animação e da música
bool animationStarted = false;

// Inicial position, rotation, and scale for the cathedral model
float modelPositionX = 0.0f;
float modelPositionY = 0.5f;
float modelPositionZ = -12.5f;
float modelRotationX = -90.0f;
float modelRotationY = 0.0f;
float modelScale = 0.080001f;

// Inicial position, rotation, and scale para as casas
float housePositions[6][3] = {
    {-10.0f, 0.1f, 10.0f},
    {-15.0f, 0.1f, 20.0f},
    {-15.0f, 0.1f, -20.0f},
    {-15.0f, 0.1f, -30.0f},
    {10.0f, 0.1f, 10.0f},
    {10.0f, 0.1f, -10.0f}
};

// Flags para as posições das janelas e portas nas casas
int houseFlags[6] = {2, 2, 4, 4, 2, 1};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawSky();
    drawGround();
    drawUnderground();
    drawLake();
    drawPillars();
    drawTrees();
    drawSnake();

    for (int i = 0; i < 6; ++i) {
        glPushMatrix();
        glTranslatef(housePositions[i][0], housePositions[i][1], housePositions[i][2]);
        drawHouse(houseFlags[i]);
        glPopMatrix();
    }

    drawSTLModel(cathedralModel, modelPositionX, modelPositionY, modelPositionZ, modelScale, modelRotationX, modelRotationY);
    glutSwapBuffers();
}

void timer(int value) {
    if (animationStarted) {
        updateSnake();
        updateCamera();
    }
    glutPostRedisplay();
    glutTimerFunc(60, timer, 0);
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    initLighting(); // Inicializa a iluminação
    initTrees(); // Inicializar as posições das árvores

    treeTexture = loadTexture("assets/arvore.png");
    groundTexture = loadTexture("assets/Dry_Pebbles_Grassy_[4K]_Diffuse.jpg");
    underGroundTexture = loadTexture("assets/PebblesSurface_1Albedo.jpg");
    snakeTexture = loadTexture("assets/snake.png"); // Carregar a textura da cobra
    // Carregar texturas e outros modelos...
    loadSTLModel("assets/Clermont-Ferrand_Cathedral.stl", cathedralModel);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        exit(0);
    } else if (key == 13) { // Enter
        if (!animationStarted) {
            animationStarted = true;
            initAudio(); // Inicializa e toca a música
            music.play();
        }
    } else if (key == '+') {
        cameraDistance -= 1.0f;
    } else if (key == '-') {
        cameraDistance += 1.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Snake 3D OpenGL");
    glutFullScreen();
    initOpenGL();
    initSnake();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}