#version 330 core
layout(location=0) out vec4 color;

in vec3 objectColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

void main()
{
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);
    float lightIntensity = 0.5;

    // Luz ambiente
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular light
    vec3 E = normalize(-FragPos);
    vec3 L = normalize(lightDir);
    vec3 H = normalize(L + E);
    float specularStrength = 0.9;
    float spec = pow(max(dot(norm, H), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = lightIntensity * ( (ambient + diffuse + specular) * objectColor );
    color = vec4(result, 1.0);
}
