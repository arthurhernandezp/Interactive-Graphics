#version 330 core
layout(location=0) out vec4 color;
uniform float intensity;
uniform float transparency;
in vec3 vColor;

void main()
{
    color = vec4(vColor * intensity, transparency);
};
