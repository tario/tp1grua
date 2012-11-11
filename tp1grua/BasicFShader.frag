#version 330
in vec3 Color;
in vec3 normal;
in vec3 position;

out vec4 FragColor;
void main()
{

		vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));

		float k1 = max(dot(light_direction, normalize(normal)), 0.0);
		float light_intensity = 0.2 + k1 * 0.8;

        FragColor = light_intensity * vec4( Color, 1.0) ;
}