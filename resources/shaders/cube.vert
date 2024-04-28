#version 430

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normalModel;
layout (location = 2) in vec4 color;

uniform mat4 MVP;
uniform mat4 model;

out vec4 materialColor;
out vec3 normalWorld;
out vec3 positionWorld;

void main()
{
	gl_Position = MVP * position;
	positionWorld = (MVP * position).xyz;

	normalWorld = mat3(model) * normalModel;
	materialColor = color;
}
