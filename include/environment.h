#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <utility>

extern std::vector<std::pair<float, float>> treePositions;

void drawGround();
void drawUnderground();
void drawPillars();
void drawTrees();
void initLighting();
void drawSky();
void initTrees();

#endif // ENVIRONMENT_H
