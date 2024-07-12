#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SEGMENTS 100

typedef struct {
    float x, y, z;
    float r, g, b;
} Segment;

extern Segment snake[MAX_SEGMENTS];
extern int numSegments;
extern float segmentSize;
extern float snakeSpeed;
extern float amplitude;
extern float frequency;

void initSnake();
void drawSnake();
void updateSnake();

#endif // SNAKE_H
