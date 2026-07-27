#include "camera.h"
#include "raymath.h"

const float CAMERA_DAMPING = 0.9f;
const float CAMERA_SPEED = 1.0f;

void cameraZoom(CameraComplex *camera, float zoomAmount)
{
    float scale = 0.2f*zoomAmount;
    camera->zoom = expf(logf(camera->zoom)+scale);
}

void cameraUpdate(CameraComplex *camera)
{
    camera->x += camera->dx;
    camera->y += camera->dy;
    camera->dx *= CAMERA_DAMPING;
    camera->dy *= CAMERA_DAMPING;
}

void cameraMove(CameraComplex *camera, float deltaX, float deltaY)
{
    camera->dx = -deltaX * CAMERA_SPEED;
    camera->dy = -deltaY * CAMERA_SPEED;
}