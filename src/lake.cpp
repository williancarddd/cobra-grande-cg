#include "lake.h"
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "textures.h"

float getWaveHeight(float x, float z, float time) {
    float waveFrequency = 0.1f;
    float waveAmplitude = 0.05f; // Altura da onda ajustada
    float tideAmplitude = 3.0f;  // Amplitude da maré
    float tideFrequency = 0.01f; // Frequência da maré

    // Cálculo da altura das ondas e da maré
    float waveHeight = sin(x * waveFrequency + time) * waveAmplitude + cos(z * waveFrequency + time) * waveAmplitude;
    float tideHeight = sin(time * tideFrequency) * tideAmplitude;

    return waveHeight + tideHeight;
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
    GLfloat light_position[] = {0.0, 1.0, 1.0, 1.0}; // Posição da luz
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

void drawLakeSurface(float time) {
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 1.0f); // Azul para a água do lago

    float baseHeight = 0.1f;    // Elevação da base do lago
    float floorSize = 100.0f;
    int grid = 5;

    for (float x = -floorSize; x < -20.0f; x += grid) {
        for (float z = -floorSize; z < floorSize; z += grid) {
            float waveHeight1 = baseHeight + getWaveHeight(x, z, time);
            float waveHeight2 = baseHeight + getWaveHeight(x + grid, z, time);
            float waveHeight3 = baseHeight + getWaveHeight(x + grid, z + grid, time);
            float waveHeight4 = baseHeight + getWaveHeight(x, z + grid, time);

            glTexCoord2f(0.0, 0.0); glVertex3f(x, waveHeight1, z);
            glTexCoord2f(1.0, 0.0); glVertex3f(x + grid, waveHeight2, z);
            glTexCoord2f(1.0, 1.0); glVertex3f(x + grid, waveHeight3, z + grid);
            glTexCoord2f(0.0, 1.0); glVertex3f(x, waveHeight4, z + grid);
        }
    }

    glEnd();
}

void drawWaveHighlights(float time) {
    float baseHeight = 0.1f;    // Elevação da base do lago
    float floorSize = 100.0f;
    int grid = 5;

    glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para os quadriculados
    glBegin(GL_QUADS);

    for (float x = -floorSize; x < -20.0f; x += grid) {
        for (float z = -floorSize; z < floorSize; z += grid) {
            float waveHeight1 = baseHeight + getWaveHeight(x, z, time);
            float waveHeight2 = baseHeight + getWaveHeight(x + grid, z, time);
            float waveHeight3 = baseHeight + getWaveHeight(x + grid, z + grid, time);
            float waveHeight4 = baseHeight + getWaveHeight(x, z + grid, time);

            // Desenha os quadriculados nas cristas das ondas
            if (waveHeight1 > baseHeight || waveHeight2 > baseHeight || waveHeight3 > baseHeight || waveHeight4 > baseHeight) {
                float squareSize = 0.1f; // Tamanho dos quadriculados

                glVertex3f(x - squareSize, waveHeight1 + squareSize, z - squareSize);
                glVertex3f(x - squareSize, waveHeight1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, waveHeight1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, waveHeight1 + squareSize, z - squareSize);
            }
        }
    }

    glEnd();
}

void drawLake() {
    static float time = 0.0f;   // Tempo para animação
    float waveSpeed = 0.06f;    // Velocidade da onda

    time += waveSpeed;

    setupWaterMaterial(); // Aplica material da água
    drawLakeSurface(time);
    drawWaveHighlights(time);
}
