#version 430 core

layout(location = 0) out vec4 outFragColor;

in vec4 materialColor;
in vec3 normalWorld;
in vec3 positionWorld;

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
uniform vec4 cameraPositionWorld;

void main()
{
	vec4 ambiant = material.ambient * materialColor;
	vec4 diffuse = material.diffuse * max(0, -dot(light.direction, normalWorld.xyz)) * materialColor;

	vec3 dc = normalize(positionWorld - cameraPositionWorld.xyz);
	vec3 dcprime = 2. * dot(dc, normalWorld) * normalWorld - dc;

	float specularCoef = pow(max(0, dot( light.direction, -dcprime)), material.shininess);
	outFragColor = (1. - specularCoef) * (ambiant + diffuse) + specularCoef * light.color;
}
