#version 330 core

out vec4 FragColor;
in vec2 ourTexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    FragColor = mix(texture(ourTexture1, ourTexCoord), texture(ourTexture2, ourTexCoord), 0.2f);
}