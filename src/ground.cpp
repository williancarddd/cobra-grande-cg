// src/ground.cpp
#include "ground.h"
#include "textures.h"
#include <GL/glut.h>

void drawGround() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    float textureRepeat = 10.0f; // Ajustar para repetir a textura
    glBegin(GL_QUADS);
    for (float x = -100.0f; x < 100.0f; x += 2.0f) {
        for (float z = -100.0f; z < 100.0f; z += 2.0f) {
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x, 0.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 100.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, 0.0f, z);
            glTexCoord2f((x + 102.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x + 2.0f, 0.0f, z + 2.0f);
            glTexCoord2f((x + 100.0f) / 200.0f * textureRepeat, (z + 102.0f) / 200.0f * textureRepeat);
            glVertex3f(x, 0.0f, z + 2.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
