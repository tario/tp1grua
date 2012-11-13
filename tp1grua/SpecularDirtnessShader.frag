#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;

uniform vec3 camera_direction;

uniform sampler2D texture1;
uniform sampler2D suciedad;
uniform sampler2D specularmap;
uniform float nivel_suciedad;

out vec4 FragColor;

void main()
{
	vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));
	vec3 nnormal = normalize(normal);

	// reflexion difusa de la luz
	float id = max(dot(light_direction, nnormal), 0.0);
	
	// reflexion especular
	vec3 reflected = reflect(light_direction, nnormal);
	float is = max(dot(reflected, camera_direction), 0.0);
	is = pow(is,14);

	
	float range = texture( suciedad, TexCoord )[0] * nivel_suciedad + 1.0 - nivel_suciedad;
	float ks = texture( specularmap, TexCoord)[0] * range;
	
	vec4 TextureColor = texture( texture1, TexCoord );
	FragColor = vec4(
		(0.2 + id) * TextureColor[0] * range + is * ks,
		(0.2 + id) * TextureColor[1] * range + is * ks,
		(0.2 + id) * TextureColor[2] * range + is * ks,
		1.0);
}