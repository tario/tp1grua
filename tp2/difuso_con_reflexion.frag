#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;
in vec3 normalx;

uniform vec3 camera_position;

// texturas para mapas difuso, de relieve y de reflexion
uniform sampler2D diffuse_map;
uniform sampler2D reflection_map;

// intensidades de la luz de ambiente, difusa y especular
uniform float ka, kd, ks;

// parametro de la luz especular
uniform float glossiness;

// intensidad del mapa difuso y de reflexion
uniform float intensidad_difuso, intensidad_reflexion;


const float h = 0.002;

#define M_PI 3.1415926535897932384626433832795

out vec4 FragColor;
void main()
{
	vec3 camera_direction = normalize(position - camera_position);
	// luz unidereccional proveniente del sol
	vec3 light_direction = normalize(vec3(0.37, 0.91, 0.13));
	vec3 nnormal = normalize(normal);

	// reflexion difusa de la luz
	float id = max(dot(-light_direction, nnormal), 0.0);
	
	// reflexion especular
	vec3 reflected = reflect(-light_direction, nnormal);
	float is =pow(
		max(dot(reflected, camera_direction), 0.0),
		glossiness);

	// aplicacion del mapa de reflexion
	vec3 point_direction = reflect(camera_direction, nnormal);
	vec3 projected_point_direction = normalize(vec3(point_direction[0], point_direction[1], 0.0));

	float angley = acos(dot(projected_point_direction, point_direction));
	float anglex = acos(dot(projected_point_direction, vec3(1.0,0.0,0.0)));
	if (point_direction[2] > 0.0) {
	  angley = -angley;
	}
	if (point_direction[1] < 0.0) {
	  anglex = -anglex;
	}
	vec2 reflection_coord = vec2(anglex / 2 / M_PI, angley / M_PI + 0.5) ;

	vec4 ColorReflexion = texture( reflection_map, reflection_coord);

	vec4 TextureColor = texture( diffuse_map, TexCoord ) * intensidad_difuso;
	FragColor = vec4(
		(ka + kd * id) * TextureColor[0] + ks * is + ColorReflexion[0] * intensidad_reflexion,
		(ka + kd * id) * TextureColor[1] + ks * is + ColorReflexion[1] * intensidad_reflexion,
		(ka + kd * id) * TextureColor[2] + ks * is + ColorReflexion[2] * intensidad_reflexion,
		1.0);
}