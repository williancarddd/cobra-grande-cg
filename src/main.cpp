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

bool animationStarted = false;

float modelPositionX = 0.0f;
float modelPositionY = 0.0f;
float modelPositionZ = -19.5f;
float modelRotationX = -90.0f;
float modelRotationY = 0.0f;
float modelScale = 0.15f;

float housePositions[6][3] = {
    {-10.0f, 0.1f, 10.0f},
    {-15.0f, 0.1f, 20.0f},
    {-15.0f, 0.1f, -20.0f},
    {-15.0f, 0.1f, -30.0f},
    {5.0f, 0.1f, 10.0f},
    {15.0f, 0.1f, -15.0f}};

int houseFlags[6] = {2, 2, 4, 4, 2, 1};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawSTLModel(cathedralModel, modelPositionX, modelPositionY, modelPositionZ, modelScale, modelRotationX, modelRotationY, 0);
    drawTrees();
    drawLake();
    drawSky();
    drawGround();
    drawUnderground();
    drawPillars();

    for (int i = 0; i < 6; ++i)
    {
        glPushMatrix();
        glTranslatef(housePositions[i][0], housePositions[i][1], housePositions[i][2]);
        drawHouse(houseFlags[i]);
        glPopMatrix();
    }
    drawSnake();
    glutSwapBuffers();
}

void timer(int value)
{
    if (animationStarted)
    {
        updateSnake();
        updateCamera();
    }
    glutPostRedisplay();
    glutTimerFunc(60, timer, 0);
}

void initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 350.0);
    glMatrixMode(GL_MODELVIEW);
    initLighting();
    initTrees();

    treeTexture = loadTexture("assets/arvore.png");
    groundTexture = loadTexture("assets/Dry_Pebbles_Grassy_[4K]_Diffuse.jpg");
    underGroundTexture = loadTexture("assets/PebblesSurface_1Albedo.jpg");
    snakeTexture = loadTexture("assets/snake.png");
    textureTopHome = loadTexture("assets/textureTopHome.png");
    textureWall = loadTexture("assets/textureWall.png");
    waterTexture = loadTexture("assets/water.png");
    texturePortAndDoors = loadTexture("assets/texturDoorAndPort.png");
    moonTexture = loadTexture("assets/moon.png");
    trunkTexture = loadTexture("assets/bark.png");
    foliageTexture = loadTexture("assets/base_grass5.png");

    loadSTLModel("assets/catedral_de_curitiba_-_cwb.stl", cathedralModel);
    loadSTLModel("assets/Head_B.STL", headModel);     // Adicionar essa linha
    loadSTLModel("assets/ship_v2_v2.stl", boatModel); // Adicionar essa linha
}

void handleKeypress(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
    else if (key == 13)
    {
        if (!animationStarted)
        {
            animationStarted = true;
            initAudio();
            music.play();
        }
    }
    else if (key == '+')
    {
        cameraDistance -= 1.0f;
    }
    else if (key == '-')
    {
        cameraDistance += 1.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
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
