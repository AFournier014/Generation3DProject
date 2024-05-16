#version 430 core

layout(location = 0) out vec4 outFragColor;

in vec2 TexCoords;
in vec3 ViewDir;

uniform sampler2D normalMap;
uniform sampler2D dudvMap;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
	vec2 distortedTexCoords = TexCoords + texture(dudvMap, TexCoords).rg * 0.05;
    vec4 reflection = texture(reflectionTexture, distortedTexCoords);
    vec4 refraction = texture(refractionTexture, distortedTexCoords);

    vec3 normal = normalize(texture(normalMap, TexCoords).rgb * 2.0 - 1.0);
    float fresnelEffect = pow(1.0 - dot(ViewDir, normal), 3);
    vec4 color = mix(refraction, reflection, fresnelEffect);

    outFragColor = color;
}