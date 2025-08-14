#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 clr;

out vec3 vColor;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(pos, 1);
    vColor = vec3(0.0f,1.0f,1.0f);
};
