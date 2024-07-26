#include "lighting.h"
#include <GL/glut.h>

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0.0f, 1.0f, 1.0f, 0.0f }; // Direção da luz do sol

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_position);
}

void setupWaterMaterial() {
    // Define propriedades do material da água
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0}; // Reflectividade do material
    GLfloat mat_shininess[] = {70.0};              // Brilho do material
    GLfloat mat_diffuse[] = {0.0, 0.5, 1.0, 0.7};  // Cor difusa do material com alguma transparência

    // Aplica as propriedades do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    // Habilita mistura (blending) para criar efeitos de transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Habilita o uso de texturas 2D
    glEnable(GL_TEXTURE_2D);

    // Configura o ambiente de iluminação
    GLfloat light_position[] = {0.0, 1.0, 1.0, 0.0}; // Posição da luz light_position[0] se refere a posição x, light_position[1] se refere a posição y, light_position[2] se refere a posição z e light_position[3] se refere a posição w
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Luz ambiente
    GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};  // Luz difusa
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; // Luz especular

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Habilita a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
