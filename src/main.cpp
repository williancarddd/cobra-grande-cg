#include <GL/glut.h>
#include <SFML/Audio.hpp>
#include <math.h>
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

#define M_PI 3.14159265358979323846

// Inicial position, rotation, and scale for the cathedral model
float modelPositionX = 0.0f;
float modelPositionY = 0.5f;
float modelPositionZ = -12.5f;
float modelRotationX = -90.0f;
float modelRotationY = 0.0f;
float modelScale = 0.080001f;

// Inicial position, rotation, and scale for the house model
float house1PositionX = -10.0f, house1PositionY = 0.0f, house1PositionZ = 10.0f;
float house2PositionX = 10.0f, house2PositionY = 0.0f, house2PositionZ = 10.0f;
float house3PositionX = -5.0f, house3PositionY = 0.0f, house3PositionZ = 10.0f;
float house4PositionX = 5.0f, house4PositionY = 0.0f, house4PositionZ = 10.0f;
float house5PositionX = 10.0f, house5PositionY = 0.0f, house5PositionZ = -5.0f;
float houseScale = 0.030001f;
float houseRotationX = -90.0f;

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
    drawSTLModel(cathedralModel, modelPositionX, modelPositionY, modelPositionZ, modelScale, modelRotationX, modelRotationY);
    drawModel(houseModel1, house1PositionX, house1PositionY, house1PositionZ, houseScale, houseRotationX);
    drawModel(houseModel2, house2PositionX, house2PositionY, house2PositionZ, houseScale, houseRotationX);
    drawModel(houseModel3, house3PositionX, house3PositionY, house3PositionZ, houseScale, houseRotationX);
    drawModel(houseModel4, house4PositionX, house4PositionY, house4PositionZ, houseScale, houseRotationX);
    drawModel(houseModel5, house5PositionX, house5PositionY, house5PositionZ, houseScale, houseRotationX);
    glutSwapBuffers();
}

void timer(int value) {
    updateSnake();
    updateCamera();
    glutPostRedisplay();
    glutTimerFunc(60, timer, 0);
}


void initOpenGL() {
    initAudio();
    
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
    // Carregar texturas e outros modelos...
    loadSTLModel("assets/Clermont-Ferrand_Cathedral.stl", cathedralModel);
    loadSTLModel("assets/scaleable_base_door_and_roofv1_merged.stl", houseModel1);
    loadSTLModel("assets/scaleable_base_door_and_roofv1_merged.stl", houseModel2);
    //loadSTLModel("assets/scaleable_base_door_and_roofv1_merged.stl", houseModel3);
    //loadSTLModel("assets/scaleable_base_door_and_roofv1_merged.stl", houseModel4);
    loadSTLModel("assets/scaleable_base_door_and_roofv1_merged.stl", houseModel5);
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
