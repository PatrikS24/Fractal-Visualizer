#pragma once

#include "camera.h"
#include "raylib.h"

typedef struct Fractal
{
  Shader fragShader;
  char *name;
  float *args;
  char **argsNames;
  int argsLocs[10];
  int argsLen;
  int resolutionLoc;
  int cameraLoc;
  int zoomLoc;
} Fractal;

typedef struct State
{
  CameraComplex camera;
  int iterations;
  int resolutionX;
  int resolutionY;
  Fractal fractals[10];
  int numOfFractals;
  int activeFractal;
  bool sidebarIsVisible;
  bool zoomAroundPointer;
} State;

State createState();
void freeState(State *appState);
