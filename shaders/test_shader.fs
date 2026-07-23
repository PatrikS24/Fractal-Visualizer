#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 resolution;

out vec4 finalColor;

void main()
{
	vec2 uv = gl_FragCoord.xy / resolution;

	finalColor = vec4(
		uv.x,
		uv.y,
		1.0,
		1.0
	);
}