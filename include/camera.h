#ifndef CAMERA_H
#define CAMERA_H

extern float cameraX, cameraY, cameraZ;
extern float cameraAngleY, cameraDistance;
extern float cameraSpeed, cameraVerticalSpeed;

void handleKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);
void updateCamera(); // Declaração da nova função de atualização da câmera

#endif // CAMERA_H
