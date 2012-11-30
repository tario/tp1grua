#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;

uniform vec3 camera_direction;
uniform sampler2D texture1;
uniform float ka, kd, ks;

out vec4 FragColor;
void main()
{
	vec4 TextureColor = texture( texture1, TexCoord );
	FragColor = TextureColor;
}