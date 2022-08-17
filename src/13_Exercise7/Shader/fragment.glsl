#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    //FragColor = vec4(ourColor, 1.0);
    //FragColor = texture(ourTexture, ourTexCoord);
    //FragColor = texture(ourTexture1, ourTexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(ourTexture1, ourTexCoord), texture(ourTexture2, vec2(-ourTexCoord.x, ourTexCoord.y)), 0.2f);
}