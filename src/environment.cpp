#include "environment.h"
#include "textures.h"
#include <GL/glut.h>

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
    for (float x = -18.0f; x <= 18.0f; x += 16.0f) {
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
