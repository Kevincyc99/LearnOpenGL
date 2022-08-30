#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 LightingColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;   //观察者位置

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    vec3 Position = vec3(model * vec4(aPos, 1.0f));
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;

    //环境光照
    float ambientStrength = 0.1f;   //环境因子
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);//为了计算θ，与实际光方向相反
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    //定义镜面强度
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    LightingColor = ambient + diffuse + specular;
}