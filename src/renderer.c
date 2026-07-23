#include "renderer.h"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

void renderBackground(Shader shader, int resLoc)
{
    float res[2] = {
		(float)GetScreenWidth(),
		(float)GetScreenHeight()
	};

	SetShaderValue(shader, resLoc, res, SHADER_UNIFORM_VEC2);


	BeginShaderMode(shader);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
	EndShaderMode();

}