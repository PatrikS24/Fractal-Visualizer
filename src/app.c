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

// -----------------------------------------------------------------------
// Fonts
// -----------------------------------------------------------------------
// Clay just needs an array of raylib Fonts indexed by fontId. We use
// raylib's built-in default font so this project builds with zero external
// assets. Swap in LoadFontEx("your-font.ttf", 48, 0, 0) for a real font.
#define FONT_ID_DEFAULT 0
static Font fonts[1];



static void HandleClayErrors(Clay_ErrorData errorData) {
    printf("Clay Error: %s\n", errorData.errorText.chars);
}


void runApp(void) {
    // Clay setup
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { 1024, 768 }, (Clay_ErrorHandler) { HandleClayErrors, 0 });

    // Raylib setup
    Clay_Raylib_Initialize(1024, 768, "Fractal visualizer", FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    fonts[FONT_ID_DEFAULT] = GetFontDefault();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        // ---- Feed input/state to Clay (every frame, before BeginLayout) ----
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() });
        Clay_Vector2 mousePos = { GetMousePosition().x, GetMousePosition().y };
        Clay_SetPointerState(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        Clay_UpdateScrollContainers(true, (Clay_Vector2){ GetMouseWheelMoveV().x, GetMouseWheelMoveV().y }, GetFrameTime());

        // ---- Build this frame's UI and get back Clay's render commands ----
        Clay_RenderCommandArray renderCommands = createUi(GetFPS(), GetFrameTime());

        
    
        // Clay's UI, drawn with plain raylib draw calls under the hood.
        Clay_Raylib_Render(renderCommands, fonts);

        EndDrawing();
    }

    Clay_Raylib_Close();
}
