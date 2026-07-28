#pragma once

#include "camera.h"
#include "raylib.h"

typedef struct Fractal {
    Shader fragShader;
    char *name;
    float *args;
    char **argsNames;
    int argsLen;
} Fractal;

typedef struct State {
    CameraComplex camera;
    int iterations;
    int resolutionX;
    int resolutionY;
    Fractal fractal;
    bool sidebarIsVisible;
    bool zoomAroundPointer;
} State;

State createState(Fractal fractal);