#include "gui.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------
// Colors
// -----------------------------------------------------------------------
#define COLOR_TRANSPARENT (Clay_Color) {   0,   0,   0,   0 }
#define COLOR_SIDEBAR     (Clay_Color) {  32,  33,  46, 235 }
#define COLOR_PANEL       (Clay_Color) {  48,  50,  68, 255 }
#define COLOR_ACCENT      (Clay_Color) { 105, 165, 255, 255 }
#define COLOR_TEXT        (Clay_Color) { 235, 235, 245, 255 }
#define COLOR_TEXT_DIM    (Clay_Color) { 160, 162, 180, 255 }


#define FONT_ID_DEFAULT 0

static void SidebarButton(Clay_String label, bool selected) {
    CLAY_AUTO_ID({
        .layout = {
            .sizing = { .width = CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(12),
        },
        .backgroundColor = selected ? COLOR_ACCENT : (Clay_Hovered() ? COLOR_PANEL : COLOR_TRANSPARENT),
        .cornerRadius = CLAY_CORNER_RADIUS(6),
    }) {
        CLAY_TEXT(label, { .fontId = FONT_ID_DEFAULT, .fontSize = 18, .textColor = selected ? (Clay_Color){20,20,30,255} : COLOR_TEXT });
    }
}

Clay_RenderCommandArray createUi(int fps, float deltaTime)
{
    Clay_BeginLayout();

    CLAY(CLAY_ID("Root"), {
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(16),
            .childGap = 16,
        },
        .backgroundColor = COLOR_TRANSPARENT, // let the 3D scene behind it show through
    }) {
        // ---------------- Sidebar ----------------
        CLAY(CLAY_ID("Sidebar"), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = { .width = CLAY_SIZING_FIXED(220), .height = CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 8,
            },
            .backgroundColor = COLOR_SIDEBAR,
            .cornerRadius = CLAY_CORNER_RADIUS(10),
        }) {
            CLAY_TEXT(CLAY_STRING("Clay + Raylib"), { .fontId = FONT_ID_DEFAULT, .fontSize = 22, .textColor = COLOR_TEXT });
            CLAY(CLAY_ID("SidebarSpacer"), { .layout = { .sizing = { .height = CLAY_SIZING_FIXED(12) } } }) {}

            SidebarButton(CLAY_STRING("Scene"), true);
            SidebarButton(CLAY_STRING("Materials"), false);
            SidebarButton(CLAY_STRING("Lighting"), false);
            SidebarButton(CLAY_STRING("Settings"), false);
        }

        // ---------------- Main content (the 3D scene shows through here) ----------------
        CLAY(CLAY_ID("MainContent"), {
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(12),
            },
            .backgroundColor = COLOR_TRANSPARENT,
        }) {
            // A small HUD panel drawn by Clay, floating over the 3D scene drawn by raylib.
            static char fpsText[32];   // <-- static lifetime, safe
            snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
            
            Clay_String fpsClayString = {
                .chars = fpsText,
                .length = (int32_t)strlen(fpsText)
            };
            
            CLAY_AUTO_ID({
                .layout = {
                    .padding = CLAY_PADDING_ALL(10),
                    .sizing = { .height = CLAY_SIZING_FIT() }   // required so text isn't clipped
                },
                .backgroundColor = COLOR_PANEL,
                .cornerRadius = CLAY_CORNER_RADIUS(6),
            }) {
                CLAY_TEXT(fpsClayString, {
                    .fontId = FONT_ID_DEFAULT,
                    .fontSize = 16,
                    .textColor = COLOR_TEXT
                });
            }
            

        }
    }

    return Clay_EndLayout(deltaTime); // deltaTime drives Clay's transition/animation API
}
