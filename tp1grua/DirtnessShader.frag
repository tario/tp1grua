#version 330
in vec2 TexCoord;
in vec3 normal;

uniform sampler2D texture1;
uniform sampler2D suciedad;
uniform float nivel_suciedad;

out vec4 FragColor;

void main()
{
	   float range = texture( suciedad, TexCoord )[0] * nivel_suciedad + 1.0 - nivel_suciedad;
	   FragColor = texture( texture1, TexCoord ) * range;
}