#version 400 core

layout (location = 0) out vec4 fragColour;

uniform vec3 cam_pos;
uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;
in vec2 uv;

void main()
{
	fragColour = vec4(1.0, 1.0, 1.0, 1.0);
}
