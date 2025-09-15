#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 clr;

out vec3 vColor;

uniform mat4 camMatrix;
uniform mat4 objPos;

void main()
{
    gl_Position = camMatrix * objPos * vec4(pos, 1);
    vColor = vec3(1.0f,1.0f,0.0f);
}
