#include "camera.h"

const float CAMERA_SPEED = 0.005f;

Vector2 ScreenToShaderPlane(Vector2 mousePos, Vector2 resolution);

void cameraZoomAroundPointer(CameraComplex *camera, Vector2 mouseScreenPos, Vector2 resolution, float zoomAmount)
{
  Vector2 mouseShaderPos = ScreenToShaderPlane(mouseScreenPos, resolution);

  float oldZoom = camera->zoom;
  float scale = 0.2f * zoomAmount;
  float newZoom = expf(logf(oldZoom) + scale);

  camera->x += mouseShaderPos.x * (1.0f / oldZoom - 1.0f / newZoom);
  camera->y += mouseShaderPos.y * (1.0f / oldZoom - 1.0f / newZoom);

  camera->zoom = newZoom;
}

void cameraZoomMiddle(CameraComplex *camera, float zoomAmount)
{
  float scale = 0.2f * zoomAmount;
  camera->zoom = expf(logf(camera->zoom) + scale);
}

void cameraMove(CameraComplex *camera, Vector2 delta)
{
  delta = Vector2Scale(delta, -1.0f / camera->zoom);
  delta = Vector2Scale(delta, CAMERA_SPEED);
  delta.y = -delta.y;
  Vector2 oldPos = {
      .x = camera->x,
      .y = camera->y};
  Vector2 newPos = Vector2Add(oldPos, delta);
  camera->x = newPos.x;
  camera->y = newPos.y;
}

Vector2 ScreenToShaderPlane(Vector2 mousePos, Vector2 resolution)
{
  Vector2 pos;

  // OpenGL Y-flip
  float openGL_MouseY = resolution.y - mousePos.y;

  // Map to -1.0 to 1.0 range
  pos.x = (mousePos.x / resolution.x) * 2.0f - 1.0f;
  pos.y = (openGL_MouseY / resolution.y) * 2.0f - 1.0f;

  // Fix aspect ratio
  pos.x *= (resolution.x / resolution.y);

  // Scale to Mandelbrot range
  pos.x *= 2.0f;
  pos.y *= 2.0f;

  return pos;
}
