#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 ViewProjection;

void main()
{
    TexCoords = aTexCoords;
    vec4 pos = ViewProjection * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}