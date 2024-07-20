#include "environment.h"
#include <GL/glut.h>
#include <iostream>

std::vector<std::pair<float, float>> treePositions; // Definição da variável

void initTrees() {
    // Define posições fixas para as árvores
    treePositions = {
        {-5.0f, 7.0f},
        {-15.0f, 6.0f},
        {-10.0f, 5.0f},
        {0.0f, 15.0f},
        {25.0f, 4.0f}
    };
}