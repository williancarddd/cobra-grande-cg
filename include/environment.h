// include/environment.h
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <utility>

extern std::vector<std::pair<float, float>> treePositions;

void initTrees();
void drawGround();
void drawUnderground();
void drawPillars();
void drawTrees();
void drawSky();
void initLighting();

#endif // ENVIRONMENT_H
