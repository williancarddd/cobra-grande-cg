#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>

#define M_PI 3.14159265358979323846
// Define a estrutura do segmento da cobra
typedef struct
{
    float x, y, z;
    float r, g, b; // Cor do segmento
} Segment;

#define MAX_SEGMENTS 100
Segment snake[MAX_SEGMENTS];
int numSegments = 80;
float segmentSize = 0.5f;
float snakeSpeed = 0.05f;
float amplitude = 1.2f; // Amplitude do movimento senoidal
float frequency = 1.0f; // Frequência do movimento senoidal
float angle = 0.0f;

GLuint treeTexture;
GLuint cathedralTexture;
GLuint groundTexture;
GLuint skySideTexture;
GLuint skyTopTexture;


// Variáveis para controlar a posição da câmera
float cameraX = 35.0f;
float cameraY = 10.0f;
float cameraZ = 15.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 35.0f;

// Função para carregar textura
GLuint loadTexture(const char *filename)
{
    GLuint texture = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    if (texture == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return texture;
}

// Função para inicializar os segmentos da cobra
void initSnake()
{
    for (int i = 0; i < numSegments; ++i)
    {
        snake[i].x = i * segmentSize;
        snake[i].y = 0.0f;
        snake[i].z = 0.0f;

        // Gradiente flamejante de vermelho a laranja a amarelo
        if (i < numSegments / 2)
        {
            snake[i].r = 1.0f;
            snake[i].g = (float)i / (numSegments / 2);
            snake[i].b = 0.0f;
        }
        else
        {
            snake[i].r = 1.0f;
            snake[i].g = 1.0f;
            snake[i].b = 0.0f;
        }
    }
}

// Função para desenhar a cobra
void drawSnake()
{
    for (int i = 0; i < numSegments; ++i)
    {
        glPushMatrix();
        glTranslatef(snake[i].x, snake[i].y, snake[i].z);
        glColor3f(snake[i].r, snake[i].g, snake[i].b);
        glutSolidCube(segmentSize);
        glPopMatrix();
    }
}



// Função para desenhar o chão com gradiente
void drawGround() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    for (float x = -20.0f; x < 20.0f; x += 2.0f)
    {
        for (float z = -20.0f; z < 20.0f; z += 2.0f)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x, 0.0f, z);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x + 2.0f, 0.0f, z);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x + 2.0f, 0.0f, z + 2.0f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x, 0.0f, z + 2.0f);
            glEnd();
        }
    }

}



// Função para desenhar árvores ao redor do plano
void drawTrees()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, treeTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para aplicar a textura

    float treeHeight = 3.0f;
    float treeWidth = 1.5f;

    for (float x = -18.0f; x <= 20.0f; x += 6.0f)
    {
        // Desenhar árvores na borda superior e inferior
        glPushMatrix();
        glTranslatef(x, 0.0f, -19.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        // Frente
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(treeWidth / 2, treeHeight, treeWidth / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-treeWidth / 2, treeHeight, treeWidth / 2);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x, 0.0f, 19.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        // Trás
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-treeWidth / 2, 0.0f, -treeWidth / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(treeWidth / 2, 0.0f, -treeWidth / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(treeWidth / 2, treeHeight, -treeWidth / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-treeWidth / 2, treeHeight, -treeWidth / 2);
        glEnd();
        glPopMatrix();
    }

    for (float z = -22.0f; z <= 20.0f; z += 6.0f)
    {
        // Desenhar árvores na borda esquerda e direita
        glPushMatrix();
        glTranslatef(-18.0f, 0.0f, z);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        // Lado esquerdo
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(treeWidth / 2, 0.0f, treeWidth / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(treeWidth / 2, treeHeight, treeWidth / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-treeWidth / 2, treeHeight, treeWidth / 2);
        glEnd();
        glPopMatrix();
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void drawCathedral() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cathedralTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para aplicar a textura

    float cathedralHeight = 5.0f;
    float cathedralWidth = 3.0f;

    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 2.0f); // Ajuste a posição conforme necessário
    glBegin(GL_QUADS);
    // Frente
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-cathedralWidth / 2, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(cathedralWidth / 2, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(cathedralWidth / 2, cathedralHeight, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-cathedralWidth / 2, cathedralHeight, 0.0f);
    glEnd();
    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}



// Função para atualizar a posição da cobra
void updateSnake()
{
    static float t = 0.0f;
    t += snakeSpeed;

    // Atualiza a posição da cabeça com movimento senoidal no plano xz
    float newX = snake[0].x - snakeSpeed;
    float newZ = amplitude * sin(frequency * newX);

    // Move os segmentos de trás para a frente
    for (int i = numSegments - 1; i > 0; --i)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].z = snake[i - 1].z;
    }

    // Atualiza a posição da cabeça
    snake[0].x = newX;
    snake[0].y = 0.0f;
    snake[0].z = newZ;

    // Mantém a cobra dentro da tela
    if (snake[0].x < -10.0f)
    {
        for (int i = 0; i < numSegments; ++i)
        {
            snake[i].x += 20.0f;
        }
    }
    if (snake[0].x > 10.0f)
    {
        for (int i = 0; i < numSegments; ++i)
        {
            snake[i].x -= 20.0f;
        }
    }
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Ajuste a posição da câmera
    drawGround(); // Desenha o chão
    drawTrees(); // Desenha as árvores
    drawSnake();
    drawCathedral(); // Desenha a catedral
    glutSwapBuffers();
}



// Função de atualização de animação
void timer(int value)
{
    updateSnake();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

// Função de teclado para fechar a tela e mover a câmera
void handleKeypress(unsigned char key, int x, int y)
{
    if (key == 27)
    { // 27 é o código ASCII para ESC
        exit(0);
    }
    else if (key == '+')
    {
        cameraDistance -= 1.0f;
    }
    else if (key == '-')
    {
        cameraDistance += 1.0f;
    }
}

// Função de teclado especial para mover a câmera
void handleSpecialKeypress(int key, int x, int y)
{
    float angleSpeed = 2.0f; // Velocidade de rotação da câmera
    switch (key)
    {
    case GLUT_KEY_LEFT:
        cameraAngleY -= angleSpeed;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += angleSpeed;
        break;
    case GLUT_KEY_UP:
        cameraY += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 1.0f;
        break;
    }
    cameraX = 35.0f * cos(cameraAngleY * M_PI / 180.0f);
    cameraZ = 35.0f * sin(cameraAngleY * M_PI / 180.0f);
    glutPostRedisplay();
}

// Função de inicialização OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo preto
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // Carrega a textura da árvore
    treeTexture = loadTexture("arvore.png");
    // Carrega a textura da catedral
    cathedralTexture = loadTexture("catedral.png");
    // Carrega a textura do chão
    groundTexture = loadTexture("groundTexture.bmp");
    // Carrega as texturas do céu
    skySideTexture = loadTexture("skySide.bmp");
    skyTopTexture = loadTexture("skyTop.bmp");
}



// Função principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Snake 3D OpenGL");
    glutFullScreen(); // Configura a janela para tela cheia
    initOpenGL();
    initSnake();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);       // Associa a função de teclado
    glutSpecialFunc(handleSpecialKeypress); // Associa a função de teclas especiais
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

// EXECUTE : g++ teste.c -o teste -lGL -lGLU -lglut -lSOIL -lm && ./teste
