#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normalModel;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texCoord;

out vec2 TexCoords;
out vec3 ViewDir;

uniform mat4 model;
uniform mat4 ViewProjection;
uniform vec3 cameraPositionWorld;

void main()
{
    vec4 worldPosition = model * position;
    ViewDir = normalize(cameraPositionWorld - worldPosition.xyz);

    TexCoords = texCoord;
    gl_Position = ViewProjection * worldPosition;
}