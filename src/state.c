#include "state.h"
#include "camera.h"
#include "raylib.h"
#include <stdio.h>

Fractal createMandelbrot(CameraComplex *camera);
void freeState(State *appState);

State createState()
{
  CameraComplex camera = (CameraComplex){.x = -0.5, .y = 0.0, .zoom = 1.0};
  Fractal mandelbrot = createMandelbrot(&camera);
  return (State){
      .camera = camera,
      .iterations = 200,
      .resolutionX = 200,
      .resolutionY = 200,
      .fractals[0] = mandelbrot,
      .numOfFractals = 1,
      .activeFractal = 0,
      .sidebarIsVisible = true,
      .zoomAroundPointer = true};
}

void loadShaderLocations(Fractal fractal)
{
  for (int i = 0; i < fractal.argsLen; i++)
  {
    fractal.argsLocs[i] = GetShaderLocation(fractal.fragShader, fractal.argsNames[i]);
  }
}

Fractal createMandelbrot(CameraComplex *camera)
{
  Shader shader = LoadShader(NULL, "shaders/mandelbrot.fs");
  int resolutionLoc = GetShaderLocation(shader, "resolution");
  int cameraLoc = GetShaderLocation(shader, "uCamera");
  int zoomLoc = GetShaderLocation(shader, "uZoom");

  Fractal mandelbrot = (Fractal){
      .fragShader = shader,
      .name = NULL,
      .args = NULL,
      .argsNames = NULL,
      .argsLocs = {0},
      .argsLen = 0,
      .resolutionLoc = resolutionLoc,
      .cameraLoc = cameraLoc,
      .zoomLoc = zoomLoc};
  return mandelbrot;
}

void freeFractal(Fractal *fractal)
{
  UnloadShader(fractal->fragShader);
}

void freeState(State *appState)
{
  for (int i = 0; i < appState->numOfFractals; i++)
  {
    freeFractal(&appState->fractals[i]);
  }
}
