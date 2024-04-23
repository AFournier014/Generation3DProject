#version 430

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 MVP;

out vec4 fragColor;

void main()
{
	gl_Position = MVP * position;

	fragColor = color;
}
