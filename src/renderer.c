#include "renderer.h"


#include "state.h"

#include <stdio.h>

void renderBackground(State *appState, int resLoc, int cameraLoc, int zoomLoc)
{
    float res[2] = {
		(float)GetScreenWidth(),
		(float)GetScreenHeight()
	};

    float camPos[2] = {
        appState->camera.x,
        appState->camera.y
    };


	SetShaderValue(appState->fractal.fragShader, resLoc, res, SHADER_UNIFORM_VEC2);
    SetShaderValue(appState->fractal.fragShader, cameraLoc, camPos, SHADER_UNIFORM_VEC2);
    SetShaderValue(appState->fractal.fragShader, zoomLoc, &(appState->camera.zoom), SHADER_UNIFORM_FLOAT);


	BeginShaderMode(appState->fractal.fragShader);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
	EndShaderMode();

}