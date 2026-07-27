#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 resolution;
uniform vec2 uCamera;
uniform float uZoom;


out vec4 finalColor;


vec2 complexSquare(vec2 a);
int mandelbrotSet(vec2 pos, int iterations);
vec4 colorPixel(int iterations, int maxIterations);

void main()
{

	// Convert to 0-1 range
    vec2 uv = gl_FragCoord.xy / resolution;
    
    // Convert to -1 to 1 range (centered)
    vec2 pos = uv * 2.0 - 1.0;
    
    // Fix aspect ratio
    pos.x *= resolution.x / resolution.y;
    
    // Scale to Mandelbrot range (-2 to 2)
    pos *= 2.0;
    
    // Zoom
    pos /= uZoom;
    
    // Move with camera
    pos += uCamera;
    
    int mandelbrotResult = mandelbrotSet(pos, 500);

	finalColor = colorPixel(mandelbrotResult, 500);
}

vec2 complexSquare(vec2 a)
{
    return vec2(a.x * a.x - a.y * a.y, 2.0 * a.x * a.y);
}

int mandelbrotSet(vec2 pos, int iterations)
{
    vec2 z = vec2(0.0, 0.0);
    for (int i = 0; i < iterations; i++)
    {
        vec2 nextZ = complexSquare(z) + pos;
        z = nextZ;
        if (length(z) > 2.0)
        {
            return i;
        }
    }
    return -1;
}

vec4 colorPixel(int iterations, int maxIterations)
{
    if (iterations == -1)
    {
        return vec4(
            0.0,
            0.0,
            0.0,
            1.0
        );
    }
    float col = 1.0 - (float(iterations) / float(maxIterations));
    return vec4(
        col,
        col,
        col,
        1.0
    );
}
