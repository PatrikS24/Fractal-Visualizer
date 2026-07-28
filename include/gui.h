#pragma once

#include "clay.h"
#include "state.h"

// Fonts
#define FONT_ID_NORMAL_16 0
#define FONT_ID_NORMAL_24 1;
#define FONT_ID_TITLE 2

void initGui(void);
Clay_RenderCommandArray createUi(State *state, int fps, float deltaTime);