#version 430 core

layout (location = 0) out vec4 outFragColor;

in vec2 fragTexCoord;

uniform sampler2D tex1;

void main()
{
	outFragColor = texture(tex1, fragTexCoord);
}
