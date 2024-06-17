#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define a estrutura do segmento da cobra
typedef struct {
    float x, y, z;
    float r, g, b; // Cor do segmento
} Segment;

#define MAX_SEGMENTS 100
Segment snake[MAX_SEGMENTS];
int numSegments = 80;
float segmentSize = 0.5f;
float snakeSpeed = 0.05f;
float amplitude = 1.2f;  // Amplitude do movimento senoidal
float frequency = 1.0f;  // Frequência do movimento senoidal
float angle = 0.0f;

GLuint waterTexture;
GLuint borderTexture;

// Função para carregar textura
GLuint loadTexture(const char* filename) {
    GLuint texture;
    int width, height;
    unsigned char* data;
    FILE* file;

    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    width = 256;
    height = 256;
    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);
    return texture;
}

// Função para inicializar os segmentos da cobra
void initSnake() {
    for (int i = 0; i < numSegments; ++i) {
        snake[i].x = -i * segmentSize;
        snake[i].y = 0.0f;
        snake[i].z = 0.0f;
        snake[i].r = 1.0f - (float)i / numSegments; // Gradiente de cor de vermelho a amarelo
        snake[i].g = (float)i / numSegments;
        snake[i].b = 0.0f;
    }
}

// Função para desenhar a cobra
void drawSnake() {
    for (int i = 0; i < numSegments; ++i) {
        glPushMatrix();
        glTranslatef(snake[i].x, snake[i].y, snake[i].z);
        glColor3f(snake[i].r, snake[i].g, snake[i].b);
        glutSolidCube(segmentSize);
        glPopMatrix();
    }
}

// Função para desenhar um lago
void drawLake() {
    float lakeRadius = 5.0f;
    int numSegments = 100;

    // Desenha a borda do lago
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, borderTexture);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para aplicar a textura
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = (lakeRadius + 0.2f) * cosf(angle);
        float z = (lakeRadius + 0.2f) * sinf(angle);
        glTexCoord2f((cosf(angle) + 1) / 2, (sinf(angle) + 1) / 2);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Desenha a água do lago
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glColor3f(1.0f, 1.0f, 1.0f); // Branco para aplicar a textura
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = lakeRadius * cosf(angle);
        float z = lakeRadius * sinf(angle);
        glTexCoord2f((cosf(angle) + 1) / 2, (sinf(angle) + 1) / 2);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Função para atualizar a posição da cobra
void updateSnake() {
    static float t = 0.0f;
    t += snakeSpeed;

    // Atualiza a posição da cabeça com movimento senoidal no plano xz
    float newX = snake[0].x + snakeSpeed;
    float newZ = amplitude * sin(frequency * newX);

    // Move os segmentos de trás para a frente
    for (int i = numSegments - 1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].z = snake[i - 1].z;
    }

    // Atualiza a posição da cabeça
    snake[0].x = newX;
    snake[0].y = 0.0f;
    snake[0].z = newZ;

    // Mantém a cobra dentro da tela
    if (snake[0].x > 10.0f) {
        for (int i = 0; i < numSegments; ++i) {
            snake[i].x -= 20.0f;
        }
    }
    if (snake[0].x < -10.0f) {
        for (int i = 0; i < numSegments; ++i) {
            snake[i].x += 20.0f;
        }
    }
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(35.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Ajuste a posição da câmera
    drawLake();
    drawSnake();
    glutSwapBuffers();
}

// Função de atualização de animação
void timer(int value) {
    updateSnake();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

// Função de teclado para fechar a tela
void handleKeypress(unsigned char key, int x, int y) {
    if (key == 27) { // 27 é o código ASCII para ESC
        exit(0);
    }
}

// Função de inicialização OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo preto
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // Carrega as texturas
    waterTexture = loadTexture("water_texture.bmp");
    borderTexture = loadTexture("border_texture.bmp");
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Snake 3D OpenGL");
    glutFullScreen();  // Configura a janela para tela cheia
    initOpenGL();
    initSnake();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress); // Associa a função de teclado
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
