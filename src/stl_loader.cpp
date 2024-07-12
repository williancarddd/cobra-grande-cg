#include "stl_loader.h"
#include <fstream>
#include <iostream>

void loadSTLModel(const char *filename, std::vector<Triangle> &model) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open STL file: " << filename << std::endl;
        exit(1);
    }
    char header[80];
    file.read(header, 80);
    unsigned int numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(unsigned int));
    model.resize(numTriangles);
    for (unsigned int i = 0; i < numTriangles; ++i) {
        Triangle& triangle = model[i];
        file.read(reinterpret_cast<char*>(triangle.normal), 3 * sizeof(float));
        for (int j = 0; j < 3; ++j) {
            file.read(reinterpret_cast<char*>(triangle.vertices[j]), 3 * sizeof(float));
        }
        file.ignore(2); // 2 bytes of attribute count
    }
    file.close();
}
