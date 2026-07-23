# Clay + Raylib Starter

A minimal, verified-working starter project combining [Clay](https://github.com/nicbarker/clay)
(a high-performance immediate-mode UI layout library) with [Raylib](https://www.raylib.com/)
as the rendering backend — plus an example of ordinary Raylib rendering (a rotating 3D cube)
running alongside Clay's UI in the same frame.

```
Clay + Raylib
┌───────────────┬─────────────────────────────────┐
│  Clay + Raylib │                                 │
│                │                                 │
│  [ Scene   ]   │                                 │
│    Materials   │      <- raw Raylib 3D scene ->  │
│    Lighting    │                                 │
│    Settings    │                                 │
│                │                                 │
└───────────────┴─────────────────────────────────┘
```

## What's in here

- `CMakeLists.txt` — fetches Raylib (via `FetchContent`, pinned to tag `5.5`) and downloads
  Clay's single header (`clay.h`) plus its Raylib renderer helper (`clay_renderer_raylib.c`),
  pinned to a specific commit so builds stay reproducible.
- `src/main.c` — sets up Clay + Raylib, builds a small sidebar UI with Clay, and renders a
  rotating 3D cube with plain Raylib calls behind/around it, all in the same frame.

No external assets are required — it uses Raylib's built-in default font, so it builds and
runs immediately.

## Build

Requires CMake 3.27+ and a C compiler.

```bash
cmake -B build
cmake --build build
```

On Linux you'll also need the X11/OpenGL headers Raylib's GLFW backend needs to configure
(only required the first time, if they aren't already installed):

```bash
sudo apt install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Run

```bash
./build/clay_raylib_app        # Linux/macOS
build\Debug\clay_raylib_app.exe   # Windows (Visual Studio generator)
```

## Where to go from here

- **Add a real font:** replace `fonts[FONT_ID_DEFAULT] = GetFontDefault();` with
  `LoadFontEx("resources/YourFont.ttf", 48, 0, 0);` and copy the `.ttf` next to the binary
  (or add a `CMake` post-build step like Clay's own examples do).
- **Add more Clay UI:** everything under `CreateLayout()` in `main.c` is just C — loops,
  `if`s, and functions (see `SidebarButton`) all work naturally as reusable "components".
- **Add scrolling containers, floating tooltips, images, etc.:** see the full API reference
  in the [Clay README](https://github.com/nicbarker/clay#readme).
- **Swap in your own 3D/2D content:** anything drawn between `BeginDrawing()` and
  `Clay_Raylib_Render(...)` in the main loop is completely ordinary Raylib code, independent
  of Clay. Give any Clay container a transparent background (`{0,0,0,0}`) to let your own
  rendering show through it.
