#version 420 core

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec4 vertexColor;

uniform mat4 MVP;

out vec3 vColor;

void main()
{
	gl_Position = MVP * vertexPosition;

	vColor = vertexColor;
}
