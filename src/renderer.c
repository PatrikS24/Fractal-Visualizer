#include "renderer.h"

#include "raylib.h"
#include "state.h"

void renderBackground(State *appState)
{
  float res[2] = {
      (float)GetScreenWidth(),
      (float)GetScreenHeight()};

  float camPos[2] = {
      appState->camera.x,
      appState->camera.y};
  Fractal active = appState->fractals[appState->activeFractal];
  // Set camera and resolustion in shader
  SetShaderValue(active.fragShader, active.resolutionLoc, res, SHADER_UNIFORM_VEC2);
  SetShaderValue(active.fragShader, active.cameraLoc, camPos, SHADER_UNIFORM_VEC2);
  SetShaderValue(active.fragShader, active.zoomLoc, &(appState->camera.zoom), SHADER_UNIFORM_FLOAT);

  // Set fractal values in shader
  for (int i = 0; i < active.argsLen; i++)
  {
    SetShaderValue(active.fragShader, active.argsLocs[i], &active.args[i], SHADER_UNIFORM_FLOAT);
  }

  BeginShaderMode(active.fragShader);
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
  EndShaderMode();
}
