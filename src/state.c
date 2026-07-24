#include "state.h"
#include "camera.h"

State createState(Fractal fractal)
{
    return (State){
        .camera = {
            .x = 0.0,
            .y = 0.0,
            .dx = 0.0,
            .dy = 0.0,
            .zoom = 1.0
        },
        .iterations = 200,
        .resolutionX = 200,
        .resolutionY = 200,
        .fractal = fractal,
        .sidebarIsVisible = true
    };
}