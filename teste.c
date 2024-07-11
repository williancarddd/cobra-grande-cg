#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Audio.hpp>

#define M_PI 3.14159265358979323846

typedef struct {
    float x, y, z;
    float r, g, b;
} Segment;

#define MAX_SEGMENTS 100
Segment snake[MAX_SEGMENTS];
int numSegments = 100;
float segmentSize = 1.0f;  // Aumentado para 1.0f
float snakeSpeed = 0.2f;
float amplitude = 1.2f;
float frequency = 0.5f;

GLuint treeTexture, groundTexture, undergroundTexture, skySideTexture, skyTopTexture;
float cameraX = 35.0f, cameraY = 10.0f, cameraZ = 15.0f;
float cameraAngleY = 0.0f, cameraDistance = 35.0f;

struct Triangle {
    float normal[3];
    float vertices[3][3];
};

std::vector<Triangle> cathedralModel, bushModel;

// Inicial position, rotation, and scale for the cathedral model
float modelPositionX = 0.0f;
float modelPositionY = 0.5f;
float modelPositionZ = -8.5f;
float modelRotationX = -90.0f;
float modelRotationY = 0.0f;
float modelScale = 0.080001f;

// Inicial position, rotation, and scale for the house model
std::vector<Triangle> houseModel1, houseModel2, houseModel3, houseModel4, houseModel5;
float house1PositionX = -10.0f, house1PositionY = 0.0f, house1PositionZ = 10.0f;
float house2PositionX = 10.0f, house2PositionY = 0.0f, house2PositionZ = 10.0f;
float house3PositionX = -5.0f, house3PositionY = 0.0f, house3PositionZ = 10.0f;
float house4PositionX = 5.0f, house4PositionY = 0.0f, house4PositionZ = 10.0f;
float house5PositionX = 10.0f, house5PositionY = 0.0f, house5PositionZ = -5.0f;
float houseScale = 0.030001f; // Ajuste conforme necessário
float houseRotationX = -90.0f;

sf::Music music;

GLuint loadTexture(const char *filename) {
    GLuint texture = SOIL_load_OGL_texture(
        filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if (!texture) {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    return texture;
}

void loadSTLModel(const char *filename, std::vector<Triangle> &model) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open STL file: " << filename << std::endl;
        exit(1);
    }
    char header[80];
    file.read(header, 80);
    unsigned int numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(unsigned int));
    model.resize(numTriangles);
    for (unsigned int i = 0; i < numTriangles; ++i) {
        Triangle& triangle = model[i];
        file.read(reinterpret_cast<char*>(triangle.normal), 3 * sizeof(float));
        for (int j = 0; j < 3; ++j) {
            file.read(reinterpret_cast<char*>(triangle.vertices[j]), 3 * sizeof(float));
        }
        file.ignore(2); // 2 bytes of attribute count
    }
    file.close();
}

void drawSTLModel(const std::vector<Triangle> &model) {
    glPushMatrix();
    glTranslatef(modelPositionX, modelPositionY, modelPositionZ);
    glScalef(modelScale, modelScale, modelScale);
    glRotatef(modelRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(modelRotationY, 0.0f, 1.0f, 0.0f);
    glColor3f(0.82f, 0.71f, 0.55f); // Light brown color
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void drawModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotateX) {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(scale, scale, scale);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza para as casas
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : model) {
        glNormal3fv(triangle.normal);
        for (int i = 0; i < 3; ++i) {
            glVertex3fv(triangle.vertices[i]);
        }
    }
    glEnd();
    glPopMatrix();
}

void initSnake() {
    for (int i = 0; i < numSegments; ++i) {
        snake[i].x = i * segmentSize;
        snake[i].y = -4.5f;  // Mover a cobra para o subterrâneo
        snake[i].z = 0.0f;
        snake[i].r = 1.0f; snake[i].g = (i < numSegments / 2) ? (float)i / (numSegments / 2) : 1.0f; snake[i].b = 0.0f;
    }
}

void drawSnake() {
    for (int i = 0; i < numSegments; ++i) {
        glPushMatrix();
        glTranslatef(snake[i].x, snake[i].y, snake[i].z);
        glColor3f(snake[i].r, snake[i].g, snake[i].b);
        glutSolidCube(segmentSize);
        glPopMatrix();
    }
}

void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    for (float x = -20.0f; x < 20.0f; x += 2.0f) {
        for (float z = -20.0f; z < 20.0f; z += 2.0f) {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 2.0f, 0.0f, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 2.0f, 0.0f, z + 2.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 2.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawUnderground() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_QUADS);
    for (float x = -20.0f; x < 20.0f; x += 2.0f) {
        for (float z = -20.0f; z < 20.0f; z += 2.0f) {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -5.0f, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 2.0f, -5.0f, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 2.0f, -5.0f, z + 2.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x, -5.0f, z + 2.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawPillars() {
    float pillarHeight = 5.0f;
    float pillarWidth = 0.5f;
    glColor3f(0.22f, 0.22f, 0.22f);
    for (float x = -18.0f; x <= 18.0f; x += 6.0f) {
        for (float z = -18.0f; z <= 18.0f; z += 6.0f) {
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

void drawBushes() {
    float bushScale = 0.05f; // Ajuste conforme necessário
    for (float x = -20.0f; x <= 20.0f; x += 5.0f) {
            drawModel(bushModel, x+5, 0.0f, 18, bushScale, -90);
            drawModel(bushModel, x+5, 0.0f, -18, bushScale, -90);
    }
}

void drawTrees() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, treeTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f);
    float treeHeight = 3.0f, treeWidth = 1.5f;
    for (float x = -18.0f; x <= 20.0f; x += 6.0f) {
        glPushMatrix();
        glTranslatef(x, 0.0f, -19.0f); glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(treeWidth / 2, treeHeight, treeWidth / 2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-treeWidth / 2, treeHeight, treeWidth / 2);
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
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
    snake[0].y = -4.5f;  // Mover a cabeça da cobra para o subterrâneo
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawGround();
    drawUnderground();
    drawPillars();
    drawTrees();
    drawSnake();
    drawSTLModel(cathedralModel);
    drawModel(houseModel1, house1PositionX, house1PositionY, house1PositionZ, houseScale, houseRotationX);
    drawModel(houseModel2, house2PositionX, house2PositionY, house2PositionZ, houseScale, houseRotationX);
    drawModel(houseModel3, house3PositionX, house3PositionY, house3PositionZ, houseScale, houseRotationX);
    drawModel(houseModel4, house4PositionX, house4PositionY, house4PositionZ, houseScale, houseRotationX);
    drawModel(houseModel5, house5PositionX, house5PositionY, house5PositionZ, houseScale, houseRotationX);
    //drawBushes();
    glutSwapBuffers();
}

void timer(int value) {
    updateSnake();
    glutPostRedisplay();
    glutTimerFunc(1000 / 120, timer, 0);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        printf("%lf", modelScale);
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

void initOpenGL() {
    if (!music.openFromFile("/home/william/Projects/CG/cobra-grande-cg/music2.ogg")) {
        std::cerr << "Error loading music file!" << std::endl;
        exit(1);
    }
    music.setLoop(true);
    music.play();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    treeTexture = loadTexture("arvore.png");
    groundTexture = loadTexture("groundTexture.bmp");
    undergroundTexture = loadTexture("undergroundTexture.bmp");
    skySideTexture = loadTexture("skySide.bmp");
    skyTopTexture = loadTexture("skyTop.bmp");
    // Carregar texturas e outros modelos...
    loadSTLModel("Clermont-Ferrand_Cathedral.stl", cathedralModel);
    loadSTLModel("scaleable_base_door_and_roofv1_merged.stl", houseModel1);
    loadSTLModel("scaleable_base_door_and_roofv1_merged.stl", houseModel2);
    loadSTLModel("scaleable_base_door_and_roofv1_merged.stl", houseModel3);
    loadSTLModel("scaleable_base_door_and_roofv1_merged.stl", houseModel4);
    loadSTLModel("scaleable_base_door_and_roofv1_merged.stl", houseModel5);
    //loadSTLModel("Bush-v3.stl", bushModel);
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


// movimento circular da cobra 
// animação da camera de cima para baixo sozinho
// mudar a textura do chão
// adicionar iluminação
// adicionar textura aos pilares

// melhorar o céu
// adicionar pedras debaixo da cidade

