#version 330 core
layout(location=0) out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

uniform float uLightIntensity;
uniform float uAmbientStrength;
uniform float uSpecularStrength;

uniform vec3 uLightColor;
uniform vec3 uObjectColor;

void main()
{
    // Luz ambiente
    vec3 ambient = uAmbientStrength * uLightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;

    // Specular light
    vec3 E = normalize(-FragPos);
    vec3 L = normalize(lightDir);
    vec3 H = normalize(L + E);

    float spec = pow(max(dot(norm, H), 0.0), 64);
    vec3 specular = uSpecularStrength * spec * uLightColor;

    vec3 result = uLightIntensity * ( (ambient + diffuse + specular) * uObjectColor );
    color = vec4(result, 1.0);
}
