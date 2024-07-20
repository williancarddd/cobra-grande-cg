#include "lake.h"
#include <GL/glut.h>
#include <cmath>
#include <vector>

void drawLake() {
    float waveHeight = 0.05f;  // Altura da onda
    float waveFrequency = 0.1f; // Frequência da onda
    float waveSpeed = 0.03f;    // Velocidade da onda
    static float time = 0.0f;   // Tempo para animação

    float baseHeight = 0.1f;    // Elevação da base do lago

    time += waveSpeed;

    // Desenha a água com ondas
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 1.0f); // Azul para a água do lago

    for (float x = -100.0f; x < -20.0f; x += 1.0f) {
        for (float z = -100.0f; z < 100.0f; z += 1.0f) {
            float y1 = baseHeight + waveHeight * sin(waveFrequency * (x + z) + time);
            float y2 = baseHeight + waveHeight * sin(waveFrequency * (x + z + 1.0f) + time);
            float y3 = baseHeight + waveHeight * sin(waveFrequency * (x + 1.0f + z + 1.0f) + time);
            float y4 = baseHeight + waveHeight * sin(waveFrequency * (x + 1.0f + z) + time);

            glVertex3f(x, y1, z);
            glVertex3f(x, y2, z + 1.0f);
            glVertex3f(x + 1.0f, y3, z + 1.0f);
            glVertex3f(x + 1.0f, y4, z);
        }
    }

    glEnd();

    // Desenha os quadriculados brancos para destacar as cristas das ondas
    glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para os quadriculados
    glBegin(GL_QUADS);

    for (float x = -100.0f; x < -20.0f; x += 1.0f) {
        for (float z = -100.0f; z < 100.0f; z += 1.0f) {
            float y1 = baseHeight + waveHeight * sin(waveFrequency * (x + z) + time);
            float y2 = baseHeight + waveHeight * sin(waveFrequency * (x + z + 1.0f) + time);
            float y3 = baseHeight + waveHeight * sin(waveFrequency * (x + 1.0f + z + 1.0f) + time);
            float y4 = baseHeight + waveHeight * sin(waveFrequency * (x + 1.0f + z) + time);

            // Desenha os quadriculados nas cristas das ondas
            if (y1 > baseHeight || y2 > baseHeight || y3 > baseHeight || y4 > baseHeight) {
                float squareSize = 0.1f; // Tamanho dos quadriculados

                glVertex3f(x - squareSize, y1 + squareSize, z - squareSize);
                glVertex3f(x - squareSize, y1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, y1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, y1 + squareSize, z - squareSize);
            }
        }
    }

    glEnd();

}

void drawStones() {
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza para as pedras

    std::vector<std::pair<float, float>> stonePositions = {
        {-100.0f, -100.0f}, {-98.0f, -100.0f}, {-97.0f, -100.0f},
        {-96.0f, -100.0f}, {-95.0f, -100.0f}, {-94.0f, -100.0f},
        {-93.0f, -100.0f}, {-92.0f, -100.0f}, {-91.0f, -100.0f},
        {-100.0f, 100.0f}, {-98.0f, 100.0f}, {-97.0f, 100.0f},
        {-96.0f, 100.0f}, {-95.0f, 100.0f}, {-94.0f, 100.0f},
        {-93.0f, 100.0f}, {-92.0f, 100.0f}, {-91.0f, 100.0f},
        {-20.0f, -100.0f}, {-20.0f, -98.0f}, {-20.0f, -97.0f},
        {-20.0f, -96.0f}, {-20.0f, -95.0f}, {-20.0f, -94.0f},
        {-20.0f, -93.0f}, {-20.0f, -92.0f}, {-20.0f, -91.0f},
        {-20.0f, 100.0f}, {-20.0f, 98.0f}, {-20.0f, 97.0f},
        {-20.0f, 96.0f}, {-20.0f, 95.0f}, {-20.0f, 94.0f},
        {-20.0f, 93.0f}, {-20.0f, 92.0f}, {-20.0f, 91.0f}
    };

    for (const auto& pos : stonePositions) {
        glPushMatrix();
        glTranslatef(pos.first, 0.15f, pos.second);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
}
