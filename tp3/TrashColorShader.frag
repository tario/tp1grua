#version 330
in vec3 normal;
in vec3 position;

uniform vec3 camera_position;
uniform vec3 Color;
uniform vec3 camera_front_direction;

out vec4 FragColor;
void main()
{
	vec3 camera_direction = normalize(position - camera_position);
	vec3 light_direction = -normalize(vec3(0.37, 0.91, 0.13));
	vec3 nnormal = normalize(normal);

	// reflexion difusa de la luz
	float k1 = max(dot(light_direction, nnormal), 0.0);
	
	// reflexion especular
	vec3 reflected = reflect(light_direction, nnormal);
	float k2 = max(dot(reflected, camera_direction), 0.0);
	k2 = pow(k2,8);

	float alpha = ( 1.0 - pow(dot(camera_front_direction,camera_direction),2) ) * 2;
	if (alpha > 1.0) alpha = 1.0;
	if (alpha < 0.0) alpha = 0.0;

	FragColor = vec4(
		(0.05 + k1) * Color[0] + k2 * 1.2,
		(0.05 + k1) * Color[1] + k2 * 1.2,
		(0.05 + k1) * Color[2] + k2 * 1.2,
		alpha);
}