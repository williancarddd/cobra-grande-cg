#ifndef SNAKE_H
#define SNAKE_H

#include <GL/glut.h>
#include <vector>

#define MAX_SEGMENTS 100

struct Segment {
    float x, y, z;
    float r, g, b;
};

extern std::vector<Segment> snake; // Alterado para std::vector
extern int numSegments;
extern float segmentSize;
extern float snakeSpeed;
extern float radius;
extern float elevationSpeed;
extern bool onSurface;
extern bool snakeDisappeared;
extern float boatX, boatY, boatZ;
extern GLuint snakeTexture; // Adicione a variável da textura

void initSnake();
void drawSnake();
void updateSnake();
void loadSnakeTexture(); // Adicione a função de carregamento da textura

#endif // SNAKE_H
