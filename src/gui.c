#include "gui.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Colors
#define COLOR_TRANSPARENT (Clay_Color) {   0,   0,   0,   0 }
#define COLOR_SIDEBAR     (Clay_Color) {  32,  33,  46, 235 }
#define COLOR_PANEL       (Clay_Color) {  48,  50,  68, 255 }
#define COLOR_ACCENT      (Clay_Color) { 105, 165, 255, 255 }
#define COLOR_TEXT        (Clay_Color) { 235, 235, 245, 255 }
#define COLOR_TEXT_DIM    (Clay_Color) { 160, 162, 180, 255 }
#define COLOR_BLACK       (Clay_Color) { 0, 0, 0, 255}
#define COLOR_WHITE       (Clay_Color) { 255, 255, 255, 255}
#define COLOR_RED         (Clay_Color) { 255, 0, 0, 255}
#define COLOR_GREEN       (Clay_Color) { 0, 255, 0, 255}

static void renderSidebar(State *state);
static void clickToggleBoolean(Clay_ElementId id, Clay_PointerData pointerData, void *userData);
static void toggleButton(bool *boolean);
static void labeledToggleButton(char *label, bool *boolean);
static void VSpacer(int minWidth);

Clay_RenderCommandArray createUi(State *state, int fps, float deltaTime)
{
    Clay_BeginLayout();

    CLAY(CLAY_IDI("Root", 0), {
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(16),
            .childGap = 16,
        },
        .backgroundColor = COLOR_TRANSPARENT, 
    }) {
        renderSidebar(state);

        CLAY(CLAY_ID("MainContent"), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(12),
                .childAlignment = {CLAY_ALIGN_X_RIGHT}
            },
            .backgroundColor = COLOR_TRANSPARENT,

        }) {
            // FPS label
            static char fpsText[32];  
            snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
            
            Clay_String fpsClayString = {
                .chars = fpsText,
                .length = (int32_t)strlen(fpsText)
            };
            
            CLAY_AUTO_ID({
                .layout = {
                    .padding = CLAY_PADDING_ALL(10),
                    .sizing = { .height = CLAY_SIZING_FIT() }
                },
                .backgroundColor = COLOR_PANEL,
                .cornerRadius = CLAY_CORNER_RADIUS(6),
            }) {
                CLAY_TEXT(fpsClayString, {
                    .fontId = FONT_ID_NORMAL_16,
                    .fontSize = 26,
                    .textColor = COLOR_TEXT
                });
            }
        }
    }

    return Clay_EndLayout(deltaTime); // deltaTime drives Clay's transition/animation API
}

static void renderSidebar(State *state)
{
    CLAY(CLAY_IDI("Sidebar", 1), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 8,
            },
            .backgroundColor = COLOR_SIDEBAR,
            .cornerRadius = CLAY_CORNER_RADIUS(10),
            .floating = {
                .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                .attachTo = CLAY_ATTACH_TO_ELEMENT_WITH_ID,
                .parentId = CLAY_IDI("Root", 0).id,
                .offset = { 16, 16 }
            }
        }) {
        // Top hide bar/button
        CLAY(CLAY_ID("CloseBar"), {
        .layout = {
            .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(7) },
        },
        .backgroundColor = COLOR_WHITE,
        .cornerRadius = CLAY_CORNER_RADIUS(10),
    })
        {
            Clay_OnHover(clickToggleBoolean, &state->sidebarIsVisible);
        }
        if (state->sidebarIsVisible)
        {
            CLAY_TEXT(CLAY_STRING("Fractal visualizer"), { .fontId = FONT_ID_TITLE, .fontSize = 36, .textColor = COLOR_TEXT });
            CLAY(CLAY_ID("SidebarSpacer"), { .layout = { .sizing = { .height = CLAY_SIZING_FIXED(12) } } }) {}
            labeledToggleButton("Zoom on pointer", &state->zoomAroundPointer);
        }
    }
}


static void clickToggleBoolean(Clay_ElementId id, Clay_PointerData pointerData, void *userData)
{
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        bool *value = userData;
        *value = !*value;
    }
}


static void toggleButton(bool *boolean) {
    CLAY_AUTO_ID({
    .layout = {
        .sizing = {
            .width = CLAY_SIZING_FIXED(40),
            .height = CLAY_SIZING_FIXED(40),
        },
        .padding = CLAY_PADDING_ALL(2),
    },
    .backgroundColor = COLOR_BLACK,
    .cornerRadius = CLAY_CORNER_RADIUS(4),
}) {
        Clay_OnHover(clickToggleBoolean, boolean);
        CLAY_AUTO_ID({
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_GROW(0),
                },
            },
            .backgroundColor = *boolean ? COLOR_GREEN : COLOR_RED,
            .cornerRadius = CLAY_CORNER_RADIUS(2),
        }) {}
    }
}

static void labeledToggleButton(char *label, bool *boolean)
{
    CLAY_AUTO_ID({
            .layout = {
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(12),
                .childAlignment = {CLAY_ALIGN_X_LEFT, CLAY_ALIGN_Y_CENTER}
            },
            .backgroundColor = COLOR_TRANSPARENT,
        }) {
        Clay_String clayLabel = {
            .isStaticallyAllocated = false,
            .length = (int32_t)strlen(label),
            .chars = label,
        };

        CLAY_TEXT(clayLabel, {
            .fontId = FONT_ID_NORMAL_16,
            .fontSize = 26,
            .textColor = COLOR_TEXT,
        });
        VSpacer(50);
        toggleButton(boolean);
        }
}

static void VSpacer(int minWidth)
{
    CLAY_AUTO_ID( { .layout = { .sizing = { .height = CLAY_SIZING_FIXED(1), .width = CLAY_SIZING_FIXED(minWidth) } } }) {}
    CLAY_AUTO_ID( { .layout = { .sizing = { .height = CLAY_SIZING_FIXED(1), .width = CLAY_SIZING_GROW(0) } } }) {}
}