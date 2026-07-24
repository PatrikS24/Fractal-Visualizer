#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "clay_renderer_raylib.c"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdlib.h>
#include <stdio.h>

#include "app.h"
#include "gui.h"
#include "renderer.h"
#include "camera.h"
#include "state.h"

// -----------------------------------------------------------------------
// Fonts
// -----------------------------------------------------------------------
// Clay just needs an array of raylib Fonts indexed by fontId. We use
// raylib's built-in default font so this project builds with zero external
// assets. Swap in LoadFontEx("your-font.ttf", 48, 0, 0) for a real font.
#define FONT_ID_DEFAULT 0
static Font fonts[1];

#define START_WIDTH 1024
#define START_HEIGHT 768

static void HandleClayErrors(Clay_ErrorData errorData) {
    printf("Clay Error: %s\n", errorData.errorText.chars);
}

void runApp(void) {
    // Init Clay 
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { 1024, 768 }, (Clay_ErrorHandler) { HandleClayErrors, 0 });

    // Init Raylib
    Clay_Raylib_Initialize(
    START_WIDTH, START_HEIGHT, "Fractal visualizer", 
    FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT
    );
    
    fonts[FONT_ID_DEFAULT] = GetFontDefault();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    Shader shader = LoadShader(NULL, "shaders/mandelbrot.fs");
    
    Fractal fractal = {
        .fragShader = shader
    };
    
    State appState = createState(fractal);
    
    
    int resolutionLoc = GetShaderLocation(shader, "resolution");

    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() });
        Clay_Vector2 mousePos = { GetMousePosition().x, GetMousePosition().y };
        Clay_SetPointerState(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        Clay_UpdateScrollContainers(true, (Clay_Vector2){ GetMouseWheelMoveV().x, GetMouseWheelMoveV().y }, GetFrameTime());
        
        BeginDrawing();
        ClearBackground(YELLOW);
        
        // Render background
        renderBackground(&appState, resolutionLoc);
        
        // Render GUI
        Clay_RenderCommandArray renderCommands = createUi(GetFPS(), GetFrameTime());
        Clay_Raylib_Render(renderCommands, fonts);

        EndDrawing();
    }

    UnloadShader(shader);
    Clay_Raylib_Close();
}
