#include "sky.h"
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <moon.h>

void drawSky() {
    glPushMatrix();
    drawMoon();

    // Desenha as estrelas
    // pontos fixos ao redor de float moonX = -120.0f, moonY = 5.0f, moonZ = -30.0f;

    glPopMatrix();
}
