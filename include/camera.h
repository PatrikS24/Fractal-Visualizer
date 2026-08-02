#pragma once

#include "raylib.h"
#include "raymath.h"

typedef struct CameraComplex
{
  float x;
  float y;
  float zoom;
} CameraComplex;

void cameraZoomAroundPointer(CameraComplex *camera, Vector2 mouseScreenPos, Vector2 resolution, float zoomAmount);
void cameraZoomMiddle(CameraComplex *camera, float zoomAmount);
void cameraMove(CameraComplex *camera, Vector2 delta);
