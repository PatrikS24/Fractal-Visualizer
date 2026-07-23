#include "camera.h"

const float CAMERA_DAMPING = 0.9f;
const float CAMERA_SPEED = 10.0f;


void cameraZoom(cameraComplex* camera, float zoomAmount)
{
    camera->zoom *= zoomAmount;
}

void cameraUpdate(cameraComplex* camera)
{
    camera->x += camera->dx;
    camera->y += camera->dy;
    camera->dx *= CAMERA_DAMPING;
    camera->dy *= CAMERA_DAMPING;
}

void cameraMove(cameraComplex* camera, float deltaX, float deltaY)
{
    camera->dx = -deltaX * CAMERA_SPEED;
    camera->dy = -deltaY * CAMERA_SPEED;
}