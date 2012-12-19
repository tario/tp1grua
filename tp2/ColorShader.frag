#version 330
in vec3 normal;
in vec3 position;

uniform vec3 camera_position;
uniform vec3 Color;

out vec4 FragColor;
void main()
{
	FragColor = vec4(
		Color,
		1.0);
}