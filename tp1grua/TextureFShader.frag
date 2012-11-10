#version 330
in vec2 TexCoord;
in float light_intensity;

uniform sampler2D texture1;
out vec4 FragColor;
void main()
{
	   FragColor = light_intensity * texture( texture1, TexCoord );
}