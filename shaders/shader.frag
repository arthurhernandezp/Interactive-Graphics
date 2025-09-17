#version 330 core
layout(location=0) out vec4 color;

in vec3 vColor;
in vec3 Normal;
in vec3 FragPos;  
in vec3 lightPos;

void main()
{
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //color = vec4(vColor * intensity * diffuse + vColor * 0.05, transparency);

    vec3 result = (ambient + diffuse) * vColor;
    color = vec4(result, 1.0);
}
