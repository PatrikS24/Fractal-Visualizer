#include "camera.h"


const float CAMERA_DAMPING = 0.9f;
const float CAMERA_SPEED = 0.005f;

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

void cameraMove(CameraComplex *camera, Vector2 delta)
{
    delta = Vector2Scale(delta, -1.0f/camera->zoom);
    delta = Vector2Scale(delta, CAMERA_SPEED);
    delta.y = -delta.y;
    Vector2 oldPos = {
        .x = camera->x,
        .y = camera->y
    };
    Vector2 newPos = Vector2Add(oldPos, delta);
    camera->x = newPos.x;
    camera->y = newPos.y;
}