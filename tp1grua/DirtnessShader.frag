#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;

uniform sampler2D texture1;
uniform sampler2D suciedad;
uniform float nivel_suciedad;

out vec4 FragColor;

void main()
{
	vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));

	float k1 = max(dot(light_direction, normalize(normal)), 0.0);
	float light_intensity = 0.2 + k1 * 0.8;

	float range = texture( suciedad, TexCoord )[0] * nivel_suciedad + 1.0 - nivel_suciedad;
	FragColor = light_intensity * texture( texture1, TexCoord ) * range;
}