#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;               //观察者位置
uniform float ambientStrength;      //环境因子
uniform float specularStrength;     //镜面强度
uniform int Shininess;              //反光度
uniform bool SpecularMethod;        //true表示用半程向量，false用反射光

void main()
{
    //环境光照
    vec3 ambient = ambientStrength * lightColor;
    //漫反射光照
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);//为了计算θ，与实际光方向相反
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;
    //镜面光照
    vec3 viewDir = normalize(viewPos - FragPos);
    //通过反射光和观察者的角度计算高光，会有一定损失(观察方向与光源在同一侧)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir), 0.0), pow(2, Shininess));
    //通过半程向量计算高光
    vec3 halfDir = normalize(lightDir + viewDir); //半程向量
    float spec2 = pow(dot(halfDir, norm), pow(2, Shininess));
    float spec;
    if (SpecularMethod)
        spec = spec2;
    else
        spec = spec1;
    vec3 specular = specularStrength * spec * lightColor;
    //Blinn-Phong反射模型
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0f);
}