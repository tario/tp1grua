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

const float h = 0.002;

#define M_PI 3.1415926535897932384626433832795

out vec4 FragColor;
void main()
{
	vec3 camera_direction = normalize(position - camera_position);
	// luz unidereccional proveniente del sol
	vec3 light_direction = normalize(vec3(21.0, 10.0, 1.0));
	// calculo de la normal, usando el mapa de normales
	vec3 normalz = normalize(normal);
	vec4 textureNormal = texture(bump_map, TexCoord) * 2 - vec4(1.0,1.0,1.0,1.0);

	vec3 normalx = normalize(normalx);
	vec3 normaly = -normalize(cross(normalz,normalx));

	
	mat3 rotNormal = mat3(normalx[0], normalx[1], normalx[2],
						normaly[0], normaly[1], normaly[2],
						normalz[0], normalz[1], normalz[2]);

	vec3 nnormal = 
		intensidad_relieve * rotNormal * normalize(vec3(textureNormal[0],textureNormal[1],textureNormal[2])) + 
		(1.0 - intensidad_relieve) * normalz;
	
	nnormal = normalize(nnormal);

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

	vec4 TextureColor = texture( diffuse_map, TexCoord ) * intensidad_difuso + 
						vec4(0.5,0.5,0.5,1.0) * intensidad_gris +
						ColorReflexion * intensidad_reflexion;
	FragColor = vec4(
		(ka + kd * id) * TextureColor[0] + ks * is,
		(ka + kd * id) * TextureColor[1] + ks * is,
		(ka + kd * id) * TextureColor[2] + ks * is,
		1.0);

	//FragColor = vec4(normalize(vec3(textureNormal[0],textureNormal[1],textureNormal[2])),1.0);
    //FragColor = vec4(light_direction, 1.0);
	//FragColor = vec4(normalz, 1.0);

}