#version 410 core

layout (location = 0) in vec3 inVert;
layout (location = 1) in vec2 inUV;

out vec2 iUV;
uniform float iTime;
uniform vec2 iMouse;

void main()
{
    iUV = inUV;
    gl_Position = vec4(inVert, 1.0);
}
