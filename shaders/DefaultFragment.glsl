#version 410 core

layout (location = 0) out vec4 fragColour;

in vec2 iUV;
uniform float iTime;
uniform vec2 iMouse;

void main()
{
	// Time varying pixel colour
	vec3 colour = 0.5 + 0.5 * cos(iTime + iUV.xyx + vec3(0, 2, 4));

	// Output to screen
	fragColour = vec4(colour, 1.0);
}
