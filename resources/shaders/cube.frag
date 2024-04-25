#version 430 core

layout(location = 0) out vec4 outFragColor;

in vec4 materialColor;
in vec3 normalWorld;

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;
	vec4 color;
};

uniform Material material;
uniform DirectionalLight light;

void main()
{
	vec4 ambiant = material.ambient * materialColor;
	vec4 diffuse = material.diffuse * max(0, -dot(light.direction, normalWorld.xyz)) * materialColor;
	vec4 specular = vec4(0);
	outFragColor = ambiant + diffuse + specular;
}
