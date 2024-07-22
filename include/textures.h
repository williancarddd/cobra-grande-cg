#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glut.h>

// Declaração de variáveis globais para texturas
extern GLuint treeTexture, groundTexture, underGroundTexture, snakeTexture;

GLuint loadTexture(const char *filename);

#endif // TEXTURES_H
