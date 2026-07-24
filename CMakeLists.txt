cmake_minimum_required(VERSION 3.27)
project(clay_raylib_app C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# ---------------------------------------------------------------------------
# Raylib
# ---------------------------------------------------------------------------
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)   # don't build raylib's own examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)   # don't build raylib's own example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

# ---------------------------------------------------------------------------
# Clay
# Clay ships as a single header (clay.h) plus a small renderer file for each
# backend. It doesn't publish a CMake package, so we just download the two
# files we need, pinned to a specific commit so builds stay reproducible.
# ---------------------------------------------------------------------------
set(CLAY_COMMIT "e6cc36941ab2af5d81107617039d6f527a1c660b")
set(CLAY_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/_deps/clay-src")
file(MAKE_DIRECTORY "${CLAY_DOWNLOAD_DIR}")

file(DOWNLOAD
    "https://raw.githubusercontent.com/nicbarker/clay/${CLAY_COMMIT}/clay.h"
    "${CLAY_DOWNLOAD_DIR}/clay.h"
)
file(DOWNLOAD
    "https://raw.githubusercontent.com/nicbarker/clay/${CLAY_COMMIT}/renderers/raylib/clay_renderer_raylib.c"
    "${CLAY_DOWNLOAD_DIR}/clay_renderer_raylib.c"
)

# ---------------------------------------------------------------------------
# App
# ---------------------------------------------------------------------------
add_executable(clay_raylib_app 
    src/main.c
    src/app.c 
    src/gui.c   
    src/camera.c
    src/renderer.c
    src/state.c
)

target_include_directories(clay_raylib_app PRIVATE ${CLAY_DOWNLOAD_DIR})
target_include_directories(clay_raylib_app PRIVATE include)
target_link_libraries(clay_raylib_app PRIVATE raylib)

# Raylib's own platform-specific link requirements (macOS frameworks, etc.)
if (APPLE)
    target_link_libraries(clay_raylib_app PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
