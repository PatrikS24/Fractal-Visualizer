#pragma once

typedef struct cameraComplex 
{
    float x;
    float y;
    float dx;
    float dy;
    float zoom;
} cameraComplex;

void cameraZoom(cameraComplex* camera, float zoomAmount);
void cameraMove(cameraComplex* camera, float deltaX, float deltaY);
void cameraUpdate(cameraComplex* camera);