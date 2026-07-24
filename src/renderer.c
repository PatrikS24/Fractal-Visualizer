#include "renderer.h"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "state.h"

void renderBackground(State *appState, int resLoc)
{
    float res[2] = {
		(float)GetScreenWidth(),
		(float)GetScreenHeight()
	};

	SetShaderValue(appState->fractal.fragShader, resLoc, res, SHADER_UNIFORM_VEC2);


	BeginShaderMode(appState->fractal.fragShader);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
	EndShaderMode();

}