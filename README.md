
## Build

Requires CMake 3.27+ and a C compiler.

```bash
cmake -B build
cmake --build build
```

On Linux you'll also need the X11/OpenGL headers Raylib's GLFW backend needs to configure


```bash
sudo apt install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Run

```bash
./build/clay_raylib_app        # Linux/macOS
build\Debug\clay_raylib_app.exe   # Windows (Visual Studio generator)
```