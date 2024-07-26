#include <moon.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <textures.h>

void drawMoon()
{
  // Desenha a lua
  float moonRadius = 10.0f;
  float moonX = -120.0f, moonY = 5.0f, moonZ = -30.0f;

  glEnable(GL_TEXTURE_2D);                   // Habilitar texturas
  glBindTexture(GL_TEXTURE_2D, moonTexture); // Vincular a textura da lua

  glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para a textura
  glPushMatrix();
  glTranslatef(moonX, moonY, moonZ);

  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE); // Habilitar mapeamento de textura
  gluSphere(quad, moonRadius, 80, 80);
  gluDeleteQuadric(quad);

  glPopMatrix();
  glDisable(GL_TEXTURE_2D); // Desabilitar texturas
}
