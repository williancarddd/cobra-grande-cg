#ifndef STL_LOADER_H
#define STL_LOADER_H

#include <vector>
#include "models.h"

void loadSTLModel(const char *filename, std::vector<Triangle> &model);

#endif // STL_LOADER_H
