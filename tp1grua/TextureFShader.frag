#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 light_direction;

uniform sampler2D texture1;
out vec4 FragColor;
void main()
{
		vec3 reflected = reflect(light_direction, normalize(normal));
		float k1 = 0.5 - dot(light_direction, reflected) * 0.5;
		float l = 0.2 + k1 * 0.8;
	   FragColor = l * texture( texture1, TexCoord );
}