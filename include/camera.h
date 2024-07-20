#ifndef CAMERA_H
#define CAMERA_H

void handleKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);
void updateCamera();

extern float cameraX, cameraY, cameraZ, cameraDistance, cameraAngleX, cameraAngleY;

#endif // CAMERA_H
