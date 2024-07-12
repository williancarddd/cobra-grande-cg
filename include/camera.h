#ifndef CAMERA_H
#define CAMERA_H

extern float cameraX, cameraY, cameraZ;
extern float cameraAngleY, cameraDistance;

void handleKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);

#endif // CAMERA_H
