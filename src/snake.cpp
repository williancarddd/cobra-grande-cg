#include "snake.h"
#include <GL/glut.h>
#include <cmath>
#include <vector>

// Variável global para a textura da cobra
extern GLuint snakeTexture;

std::vector<Segment> snake;
int numSegments = 30; // Redução do número de segmentos
float segmentSize = 0.6f; // Tamanho ajustado do segmento
float snakeSpeed = 0.05f; // Ajuste para movimento suave
float radius = 5.0f;
float elevationSpeed = 0.04f;  // Ajuste para elevação suave
bool onSurface = false;        // Flag para verificar se a cobra está na superfície
bool snakeDisappeared = false; // Flag para verificar se a cobra desapareceu
float boatX, boatY, boatZ;     // Posição do barco

void initSnake()
{
    snake.resize(numSegments);
    for (int i = 0; i < numSegments; ++i)
    {
        snake[i].x = radius * cos(i * 2 * M_PI / numSegments);
        snake[i].y = -4.5f;
        snake[i].z = radius * sin(i * 2 * M_PI / numSegments);
        snake[i].r = 1.0f;
        snake[i].g = (i < numSegments / 2) ? (float)i / (numSegments / 2) : 1.0f;
        snake[i].b = 0.0f;
    }
}

void drawBoat(float x, float y, float z)
{
    // Desenha um barco simples na posição especificada
    glColor3f(0.3f, 0.2f, 0.1f); // Marrom para o barco
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(2.0f, 0.5f, 1.0f);
    glutSolidCube(segmentSize * 5); // Tamanho ajustado do barco
    glPopMatrix();
}

void drawSnake()
{
    if (snakeDisappeared)
    {
        drawBoat(boatX, boatY, boatZ);
    }
    else
    {
        glEnable(GL_TEXTURE_2D); // Habilitar texturas
        glBindTexture(GL_TEXTURE_2D, snakeTexture); // Vincular a textura da cobra

        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);

        for (int i = 0; i < numSegments - 1; ++i)
        {
            float dx = snake[i + 1].x - snake[i].x;
            float dy = snake[i + 1].y - snake[i].y;
            float dz = snake[i + 1].z - snake[i].z;

            float length = sqrt(dx * dx + dy * dy + dz * dz);

            glPushMatrix();
            glTranslatef(snake[i].x, snake[i].y, snake[i].z);

            float angleX = atan2(dy, length) * 180.0 / M_PI;
            float angleZ = atan2(dx, dz) * 180.0 / M_PI;

            glRotatef(angleZ, 0.0f, 1.0f, 0.0f);
            glRotatef(angleX, 1.0f, 0.0f, 0.0f);

            gluCylinder(quad, segmentSize * 0.4f, segmentSize * 0.4f, length, 32, 32);
            gluDisk(quad, 0, segmentSize * 0.4f, 32, 1); // Fechar a base do cilindro
            glTranslatef(0, 0, length);
            gluDisk(quad, 0, segmentSize * 0.4f, 32, 1); // Fechar o topo do cilindro

            glPopMatrix();
        }

        gluDeleteQuadric(quad);
        glDisable(GL_TEXTURE_2D); // Desabilitar texturas
    }
}

void updateSnake()
{
    static float angle = 0.0f;
    static float totalAngle = 0.0f;
    angle += snakeSpeed;
    totalAngle += snakeSpeed;

    if (!onSurface)
    {
        // Elevação suave da cobra
        snake[0].x = radius * cos(angle);
        snake[0].y += elevationSpeed;
        snake[0].z = radius * sin(angle);

        if (snake[0].y >= 0.0f)
        {
            onSurface = true;
            for (int i = 0; i < numSegments; ++i)
            {
                snake[i].y = 0.0f; // Ajuste final da elevação
            }
        }
    }
    else if (totalAngle < 4 * M_PI)
    {
        // Cobra dá duas voltas ao redor do ponto inicial
        snake[0].x = radius * cos(angle);
        snake[0].z = radius * sin(angle);
    }
    else
    {
        // Cobra segue em linha reta
        snake[0].x -= 0.4;

        // Cobra atinge a posição x = -20 e desaparece
        if (snake[0].x <= -20.0f)
        {
            snakeDisappeared = true;
            boatX = snake[0].x;
            boatY = snake[0].y;
            boatZ = snake[0].z;
        }
    }

    // Atualiza os segmentos da cobra com interpolação suave
    for (int i = numSegments - 1; i > 0; --i)
    {
        snake[i].x += (snake[i - 1].x - snake[i].x) * 1.0;
        snake[i].y += (snake[i - 1].y - snake[i].y) * 1.0;
        snake[i].z += (snake[i - 1].z - snake[i].z) * 1.0;
    }
}
