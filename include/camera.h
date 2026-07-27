#pragma once

#include "raylib.h"
#include "raymath.h"

typedef struct CameraComplex
{
    float x;
    float y;
    float dx;
    float dy;
    float zoom;
} CameraComplex;

void cameraZoom(CameraComplex* camera, float zoomAmount);
void cameraMove(CameraComplex* camera, Vector2 delta);
void cameraUpdate(CameraComplex* camera);
