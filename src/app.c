#include "app.h"

#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "clay_renderer_raylib.c"

#include "rlgl.h"
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "gui.h"
#include "renderer.h"
#include "state.h"

static Font fonts[3];
// Dimentions
#define START_WIDTH 1024
#define START_HEIGHT 768

static void HandleClayErrors(Clay_ErrorData errorData)
{
  printf("Clay Error: %s\n", errorData.errorText.chars);
}

void loadFont(uint32_t fontId, int fontSize, const char *path)
{
  fonts[fontId] = LoadFontEx(path, fontSize * 2, NULL, 0);
  SetTextureFilter(fonts[fontId].texture, TEXTURE_FILTER_TRILINEAR);
}

void runApp(void)
{
  // Init Clay
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
  Clay_Initialize(clayMemory, (Clay_Dimensions){1024, 768},
                  (Clay_ErrorHandler){HandleClayErrors, 0});

  // Init Raylib
  Clay_Raylib_Initialize(START_WIDTH, START_HEIGHT, "Fractal visualizer",
                         FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT |
                             FLAG_MSAA_4X_HINT);

  loadFont(0, 16, "resources/RomanSerif.ttf");
  loadFont(1, 24, "resources/RomanSerif.ttf");
  loadFont(2, 32, "resources/RomanSerif.ttf");

  Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

  State appState = createState();

  while (!WindowShouldClose())
  {
    Clay_SetLayoutDimensions((Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()});
    Clay_Vector2 mousePos = {GetMousePosition().x, GetMousePosition().y};
    Clay_SetPointerState(mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT));
    Clay_UpdateScrollContainers(
        true, (Clay_Vector2){GetMouseWheelMoveV().x, GetMouseWheelMoveV().y},
        GetFrameTime());

    BeginDrawing();
    ClearBackground(YELLOW);

    Clay_String mainId = CLAY_STRING("MainContent");
    // Main camera movement
    if (IsMouseButtonDown(0) && Clay_PointerOver(Clay_GetElementId(mainId)))
    {
      Vector2 mouseDelta = GetMouseDelta();
      cameraMove(&appState.camera, mouseDelta);
    }
    float wheel = GetMouseWheelMove();
    if (wheel != 0 && Clay_PointerOver(Clay_GetElementId(mainId)))
    {
      if (appState.zoomAroundPointer)
      {
        Vector2 resolution = {(float)GetScreenWidth(),
                              (float)GetScreenHeight()};
        cameraZoomAroundPointer(&appState.camera, GetMousePosition(),
                                resolution, wheel);
      }
      else
      {
        cameraZoomMiddle(&appState.camera, wheel);
      }
    }

    // Render background
    renderBackground(&appState);

    // Render GUI
    Clay_RenderCommandArray renderCommands =
        createUi(&appState, GetFPS(), GetFrameTime());
    Clay_Raylib_Render(renderCommands, fonts);

    EndDrawing();
  }
  UnloadFont(fonts[0]);
  UnloadFont(fonts[1]);
  UnloadFont(fonts[2]);
  freeState(&appState);
  Clay_Raylib_Close();
}
