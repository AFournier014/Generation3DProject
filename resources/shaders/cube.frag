#version 430 core

layout(location = 0) out vec4 outFragColor;

in vec4 fragColor;

void main()
{
	outFragColor = fragColor;
}
