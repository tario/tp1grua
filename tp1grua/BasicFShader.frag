#version 330
in vec3 Color;
in vec3 normal;
in vec3 position;

uniform vec3 camera_direction;

out vec4 FragColor;
void main()
{
	vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));
	vec3 nnormal = normalize(normal);

	// reflexion difusa de la luz
	float k1 = max(dot(light_direction, nnormal), 0.0);
	
	// reflexion especular
	vec3 reflected = reflect(light_direction, nnormal);
	float k2 = max(dot(reflected, camera_direction), 0.0);

	float light_intensity = 0.2 + k1 * 0.4 + k2 * 0.4;

        FragColor = light_intensity * vec4( Color, 1.0) ;
}