#version 430

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec4 vertexColor;

uniform mat4 MVP;

out vec4 inputFragColor;

void main()
{
	gl_Position = MVP * vertexPosition;

	inputFragColor = vertexColor;
}
