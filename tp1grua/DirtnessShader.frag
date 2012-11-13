#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;

uniform vec3 camera_direction;

uniform sampler2D texture1;
uniform sampler2D suciedad;
uniform float nivel_suciedad;

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
	k2 = pow(k2,6);
	
	//float light_intensity = 0.2 + k1 * 0.4 + k2 * 0.4;

	float range = texture( suciedad, TexCoord )[0] * nivel_suciedad + 1.0 - nivel_suciedad;
	
	vec4 TextureColor = texture( texture1, TexCoord );
	FragColor = vec4(
		(0.2 + k1) * TextureColor[0] * range + k2 * 0.4,
		(0.2 + k1) * TextureColor[1] * range + k2 * 0.4,
		(0.2 + k1) * TextureColor[2] * range + k2 * 0.4,
		1.0);
}