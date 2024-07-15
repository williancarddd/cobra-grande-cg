// src/environment.cpp
#include "environment.h"
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>

std::vector<std::pair<float, float>> treePositions; // Definição da variável

void initTrees() {
    srand(static_cast<unsigned int>(time(NULL)));

    for (int i = 0; i < 50; ++i) { // Adiciona 50 posições de árvores
        float x = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(100.0f))); // Gera um valor entre -50.0f e 50.0f
        float z = -50.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(100.0f))); // Gera um valor entre -50.0f e 50.0f
        treePositions.emplace_back(x, z);
    }
}
