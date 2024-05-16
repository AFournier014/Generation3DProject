#version 430 core

layout(location = 0) out vec4 outFragColor;

in vec2 materialTexCoord;
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
uniform DirectionalLight directionalLights;
uniform vec3 cameraPositionWorld;
uniform sampler2D materialTexture;

void main()
{
	vec4 materialColor = texture(materialTexture, materialTexCoord);

	vec4 ambiant = material.ambient * materialColor;

	vec3 lightDirection = normalize(directionalLights.direction);
	float diff = max(0, dot(lightDirection, normalWorld));
	vec4 diffuse = material.diffuse * diff * materialColor;

	vec3 viewDirection = normalize(cameraPositionWorld - positionWorld);
	vec3 reflectDirection = reflect(-viewDirection, normalWorld);
	float spec = pow(max(0, -dot(reflectDirection, lightDirection)), material.shininess);
	vec4 specular = material.specular * spec * directionalLights.color;

	outFragColor = ambiant + diffuse + specular;
}