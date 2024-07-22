#ifndef HOUSE_H
#define HOUSE_H

#include <GL/glut.h>  // Adicione esta linha para incluir a biblioteca OpenGL

// Declaração de variáveis globais para texturas da casa
extern GLuint textureTopHome;
extern GLuint textureWall;
extern GLuint texturePortAndDoors;

void drawHouse(int flag);

#endif // HOUSE_H
