#version 330 core
out vec4 FragColor;

//材质结构体
struct Material {
    sampler2D diffuse;  //漫反射贴图
    sampler2D specular;
    //sampler2D emission;
    float shininess;
}; 
  
//光源结构体-定向光
struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;   //观察者位置
uniform Material material;
uniform Light light;

void main()
{
    
    //环境光照
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    //漫反射光照
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);    //取反，获得一个从片段指向光源的向量
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    //定义镜面强度
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir = normalize(lightDir + viewDir); //半程向量
    float spec = pow(dot(halfDir, norm), material.shininess);
    vec3 specular = light.specular * spec * (vec3(texture(material.specular, TexCoords)));

    //放射光贴图
    //vec3 emission = vec3(texture(material.emission, TexCoords));
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}