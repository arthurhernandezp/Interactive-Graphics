#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 aNormal;

out vec3 vColor;
out vec3 FragPos;
out vec3 Normal;
out vec3 lightPos;

uniform mat4 camMatrix;
uniform mat4 objPos;
uniform vec3 ulightPos;

uniform mat4 modelView;
uniform mat3 normalMatrix;

void main()
{
    FragPos = vec3(modelView * objPos * vec4(pos, 1.0));
    Normal = normalMatrix * mat3(objPos) * aNormal;
    lightPos = vec3(modelView * vec4(ulightPos, 1.0));
    gl_Position = camMatrix * objPos * vec4(pos, 1);
    vColor = vec3(0.0f,0.0f,1.0f);
}
