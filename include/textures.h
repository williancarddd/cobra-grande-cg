#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glut.h>

extern GLuint treeTexture;
extern GLuint groundTexture;
extern GLuint underGroundTexture;
extern GLuint snakeTexture; // Adicione a declaração da textura da cobra

GLuint loadTexture(const char* filename);

#endif
