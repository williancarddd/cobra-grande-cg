#include "lake.h"
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "textures.h"
#include "lighting.h"

float getWaveHeight(float x, float z, float time)
{
    float waveFrequency = 0.1f;
    float waveAmplitude = 0.05f; // Altura da onda ajustada

    // Cálculo da altura das ondas
    float waveHeight = sin(x * waveFrequency + time) * waveAmplitude + cos(z * waveFrequency + time) * waveAmplitude;

    return waveHeight;
}

void drawLakeSurface(float time)
{
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 1.0f); // Azul para a água do lago

    float baseHeight = 0.1f; // Elevação da base do lago
    float floorSize = 100.0f;
    int grid = 5;

    for (float x = -floorSize; x < -25.0f; x += grid)
    {
        for (float z = -floorSize; z < floorSize; z += grid)
        {
            float waveHeight1 = baseHeight + getWaveHeight(x, z, time);
            float waveHeight2 = baseHeight + getWaveHeight(x + grid, z, time);
            float waveHeight3 = baseHeight + getWaveHeight(x + grid, z + grid, time);
            float waveHeight4 = baseHeight + getWaveHeight(x, z + grid, time);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(x, waveHeight1, z);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(x + grid, waveHeight2, z);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(x + grid, waveHeight3, z + grid);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(x, waveHeight4, z + grid);
        }
    }

    glEnd();
}

void drawWaveHighlights(float time)
{
    float baseHeight = 0.1f; // Elevação da base do lago
    float floorSize = 100.0f;
    int grid = 5;

    glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para os quadriculados
    glBegin(GL_QUADS);

    for (float x = -floorSize; x < -25.0f; x += grid)
    {
        for (float z = -floorSize; z < floorSize; z += grid)
        {
            float waveHeight1 = baseHeight + getWaveHeight(x, z, time);
            float waveHeight2 = baseHeight + getWaveHeight(x + grid, z, time);
            float waveHeight3 = baseHeight + getWaveHeight(x + grid, z + grid, time);
            float waveHeight4 = baseHeight + getWaveHeight(x, z + grid, time);

            // Desenha os quadriculados nas cristas das ondas
            if (waveHeight1 > baseHeight || waveHeight2 > baseHeight || waveHeight3 > baseHeight || waveHeight4 > baseHeight)
            {
                float squareSize = 0.02f; // Tamanho dos quadriculados

                glVertex3f(x - squareSize, waveHeight1 + squareSize, z - squareSize);
                glVertex3f(x - squareSize, waveHeight1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, waveHeight1 + squareSize, z + squareSize);
                glVertex3f(x + squareSize, waveHeight1 + squareSize, z - squareSize);
            }
        }
    }

    glEnd();
}

void drawLake()
{
    static float time = 0.0f; // Tempo para animação
    float waveSpeed = 0.06f;  // Velocidade da onda

    time += waveSpeed;

    glPushMatrix();
    setupWaterMaterial(); // Aplica material da água
    drawLakeSurface(time);
    drawWaveHighlights(time);
    glPopMatrix();
}
