#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;

uniform vec3 camera_direction;

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

out vec4 FragColor;
void main()
{
	vec3 light_direction = normalize(vec3(10.0, -0.14, -1.0));
	// calculo de la normal, usando el mapa de normales
	vec3 nnormal = normalize(normal);
	vec4 textureNormal = ( texture(bump_map, TexCoord) - vec4(0.5,0.5,0.5,0.5) ) * 2;

	float sinb = -textureNormal[0];
	float cosb = sqrt(1-sinb*sinb);
	float sina = -textureNormal[1]/cosb;
	float cosa = textureNormal[2]/cosb;

	mat3 rot1 = mat3(1.0, 0.0, 0.0,
					0.0, cosa, -sina,
					0.0, sina, cosa );
	mat3 rot2 = mat3(cosb, 0.0, -sinb,
					0.0, 1.0, 0.0,
					sinb, 0.0, cosb );

	
	nnormal = rot1 * rot2 * nnormal;

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