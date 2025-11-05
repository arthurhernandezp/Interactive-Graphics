#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec3 lightPos;
out vec2 texCoord;

uniform mat4 mvp;

uniform vec3 ulightPos;

uniform mat4 modelViewFrag;
uniform mat4 modelViewLight;
uniform mat3 normalMatrix;

void main()
{
    FragPos = vec3(modelViewFrag * vec4(pos, 1.0));
    Normal = normalMatrix * aNormal;
    lightPos = vec3(modelViewLight * vec4(ulightPos, 1.0));
    gl_Position = mvp * vec4(pos, 1);
    texCoord = aTexCoord;
}
