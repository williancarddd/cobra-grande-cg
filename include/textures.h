#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glut.h>

extern GLuint treeTexture, groundTexture, underGroundTexture;

GLuint loadTexture(const char *filename);

#endif // TEXTURES_H
