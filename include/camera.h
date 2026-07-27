#pragma once

typedef struct CameraComplex
{
    float x;
    float y;
    float dx;
    float dy;
    float zoom;
} CameraComplex;

void cameraZoom(CameraComplex* camera, float zoomAmount);
void cameraMove(CameraComplex* camera, float deltaX, float deltaY);
void cameraUpdate(CameraComplex* camera);
