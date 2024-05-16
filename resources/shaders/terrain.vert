#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texCoord;

uniform mat4 model;
uniform mat4 ViewProjection;

out vec2 materialTexCoord;
out vec3 normalWorld;
out vec3 positionWorld;

void main()
{
	mat4 modelViewProjection = ViewProjection * model;
	gl_Position = modelViewProjection * position;

	positionWorld = (model * position).xyz;

	normalWorld = mat3(model) * normal;

	materialTexCoord = texCoord;
}