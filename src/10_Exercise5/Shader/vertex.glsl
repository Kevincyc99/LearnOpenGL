#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float offset_Horizontal;

void main()
{
    gl_Position = vec4(aPos.x + offset_Horizontal, aPos.yz, 1.0f);
    ourColor = aColor;
}