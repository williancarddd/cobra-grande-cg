#include "snake.h"
#include <GL/glut.h>
#include <cmath>
#include "models.h"

// Variável global para a textura da cobra
extern GLuint snakeTexture;
extern std::vector<Triangle> boatModel;

std::vector<Segment> snake;
int numSegments = 55;        // Número de segmentos
float segmentSize = 1.5f;    // Tamanho do segmento
float snakeSpeed = 0.05f;    // Velocidade do movimento da cobra
float radius = 6.0f;
float elevationSpeed = 0.07f; // Velocidade de elevação da cobra
bool onSurface = false;       // Flag para verificar se a cobra está na superfície
bool snakeDisappeared = false; // Flag para verificar se a cobra desapareceu
float boatX, boatY, boatZ;     // Posição do barco
float boatAngle = 0.0f;        // Ângulo de rotação do barco
float boatSpeed = 0.03f;       // Velocidade do barco
float snakeSpeed2 = 0.11f;
float amplitude = -1.2f;
float frequency = 1.0f;
int boatPhase = 0;             // Fase atual do movimento do barco
bool snakeReturn = false;      // Flag para verificar se a cobra está retornando
bool snakeCirculo = false;     // Flag para o movimento circular
int appearingSegments = 0;     // Inicialização correta para garantir que a cobra apareça no início

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

void drawBoat(float x, float y, float z, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotação em torno do eixo Y
    drawSTLModel(boatModel, 0, 0, 0, 0.05f, -90.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void drawSnakeSegment(const Segment &segment, float segmentSize)
{
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glPushMatrix();
    glTranslatef(segment.x, segment.y, segment.z);
    gluSphere(quad, segmentSize * 0.6f, 32, 32);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void drawSnake()
{
    glPushMatrix();
    if (snakeDisappeared)
    {
        drawBoat(snake[0].x, snake[0].y, snake[0].z, boatAngle); // Utiliza o ângulo atualizado
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, snakeTexture);

        for (int i = 0; i < numSegments; ++i)
        {
            if (snake[i].x > -25.0f || snakeReturn || snakeCirculo)
            {
                drawSnakeSegment(snake[i], segmentSize);
            }
        }

        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void updateSnake()
{
    static float angle = 0.0f;
    static float totalAngle = 0.0f;

    if (!snakeDisappeared && !snakeReturn && !snakeCirculo)
    {
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
            }
        }
        else if (totalAngle < 4 * M_PI)
        {
            // Cobra dá duas voltas ao redor do ponto inicial
            snake[0].y = 0.5f;
            snake[0].x = radius * cos(angle);
            snake[0].z = radius * sin(angle);
        }
        else
        {
            if (snake[0].x > -25.0f)
            {
                // Cobra segue em linha reta com movimento senoidal em direção ao lago
                float newX = snake[0].x - snakeSpeed2;
                float newZ = amplitude * sin(frequency * newX);

                snake[0].x = newX;
                snake[0].z = newZ;
            }
            else
            {
                // Cobra atinge a posição x = -25 e desaparece
                snakeDisappeared = true;
                appearingSegments = 0; // Resetar para que apareça gradualmente no retorno
            }
        }
    }
    else if (snakeDisappeared)
    {
        switch (boatPhase)
        {
        case 0:
            if (snake[0].x > -50.0f)
            {
                // Movimento do barco em linha reta até x = -50
                snake[0].x -= snakeSpeed2 + 0.04f;
            }
            else
            {
                boatPhase++;
                boatAngle = 270.0f; // Virar para a direita
            }
            break;
        case 1:
            if (snake[0].z > -25.0f)
            {
                // Movimento do barco em linha reta até z = -25
                snake[0].z -= snakeSpeed2 + 0.04f;
            }
            else
            {
                boatPhase++;
                boatAngle = 180.0f; // Virar para a esquerda
            }
            break;
        case 2:
            if (snake[0].x < -35.0f)
            {
                // Movimento do barco em linha reta até x = -35
                snake[0].x += snakeSpeed2 + 0.04f;
            }
            else
            {
                boatPhase++;
                boatAngle = 90.0f; // Virar para cima
            }
            break;
        case 3:
            if (snake[0].z < 0.0f)
            {
                // Movimento do barco em linha reta até z = 0
                snake[0].z += snakeSpeed2 + 0.04f;
            }
            else
            {
                boatPhase++;
                boatAngle = 180.0f; // Virar para a esquerda
            }
            break;
        case 4:
            if (snake[0].x <= -25.0f)
            {
                // Movimento do barco em linha reta até x = -25
                snake[0].x += snakeSpeed2 + 0.04f;
            }
            else
            {
                boatPhase++;
                boatAngle = 0.0f; // Barco chegou ao destino final
                snakeReturn = true;
                snakeDisappeared = false;
                appearingSegments = 0; // Resetar para o retorno gradual dos segmentos
            }
            break;
        }
    }
    else if (snakeReturn)
    {
        if (snake[0].x < 0.0f)
        {
            // Movimento da cobra de volta à posição inicial
            snake[0].x += snakeSpeed2;
            snake[0].z = amplitude * sin(frequency * snake[0].x);

            // Gradualmente adicionar segmentos de volta
            if (appearingSegments < numSegments && snake[appearingSegments].x > -25.0f)
            {
                appearingSegments++;
            }
        }
        else
        {
            snakeReturn = false;
            snakeCirculo = true;
            appearingSegments = numSegments; // Certificar-se de que todos os segmentos aparecem
        }
    }
    if (snakeCirculo)
    {
        angle += snakeSpeed;
        snake[0].x = radius * cos(angle);
        snake[0].z = radius * sin(angle);
    }

    // Atualiza os segmentos da cobra com interpolação suave
    for (int i = numSegments - 1; i > 0; --i)
    {
        snake[i].x += (snake[i - 1].x - snake[i].x) * 0.5f;
        snake[i].y += (snake[i - 1].y - snake[i].y) * 0.5f;
        snake[i].z += (snake[i - 1].z - snake[i].z) * 0.5f;
    }
}
