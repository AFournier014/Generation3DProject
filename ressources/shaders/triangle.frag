#version 430 core

layout(location = 0) out vec4 outputFragColor;

in vec4 inputFragColor;
out vec4 fragColor;

void main()
{
	outputFragColor = inputFragColor;
}