#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <GL/glut.h>

struct Triangle {
    float normal[3];
    float vertices[3][3];
};

extern std::vector<Triangle> cathedralModel, houseModel1, houseModel2, houseModel3, houseModel4, houseModel5;

void drawSTLModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotX, float rotY);
void drawModel(const std::vector<Triangle> &model, float posX, float posY, float posZ, float scale, float rotateX);

#endif // MODELS_H
