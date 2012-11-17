#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;
in vec3 normalx;

uniform vec3 camera_position;

// texturas para mapas difuso, de relieve y de reflexion
uniform sampler2D diffuse_map;
uniform sampler2D bump_map;
uniform sampler2D reflection_map;

// intensidades de la luz de ambiente, difusa y especular
uniform float ka, kd, ks;

// parametro de la luz especular
uniform float glossiness;

// intensidad del mapa difuso, de reflexion y gris solido
uniform float intensidad_difuso, intensidad_reflexion, intensidad_gris;

// intensidad de mapa de relieve
uniform float intensidad_relieve;

out vec4 FragColor;
void main()
{
	vec3 camera_direction = normalize(position - camera_position);
	vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));
	// calculo de la normal, usando el mapa de normales
	vec3 normalz = normalize(normal);
	vec4 textureNormal = ( texture(bump_map, TexCoord) - vec4(0.5,0.5,0.5,0.5) ) * 2;

	vec3 normaly = normalize(cross(normal,normalx));
	vec3 normalx = normalize(normalx);

	mat3 rotNormal = mat3(normalx[0], normaly[0], normalz[0],
						normalx[1], normaly[1], normalz[1],
						normalx[2], normaly[2], normalz[2]);

	vec3 nnormal = 
		intensidad_relieve * rotNormal * normalize(vec3(textureNormal[0],textureNormal[1],textureNormal[2])) + 
		(1.0 - intensidad_relieve) * normalz;
	
	nnormal = normalize(nnormal);

	// reflexion difusa de la luz
	float id = max(dot(light_direction, nnormal), 0.0);
	
	// reflexion especular
	vec3 reflected = reflect(light_direction, nnormal);
	float is =pow(
		max(dot(reflected, camera_direction), 0.0),
		glossiness);

	vec4 TextureColor = texture( diffuse_map, TexCoord ) * intensidad_difuso + 
						vec4(0.5,0.5,0.5,1.0) * intensidad_gris;
	FragColor = vec4(
		(ka + kd * id) * TextureColor[0] + ks * is,
		(ka + kd * id) * TextureColor[1] + ks * is,
		(ka + kd * id) * TextureColor[2] + ks * is,
		1.0);
}