#version 330
in vec2 TexCoord;
in vec3 normal;
in vec3 position;
in vec3 normalx;

uniform vec3 camera_position;

// texturas para mapas difuso, de relieve y de reflexion
uniform sampler2D diffuse_map;
uniform sampler2D normal_map;

// intensidades de la luz de ambiente, difusa y especular
uniform float ka, kd, ks;

// parametro de la luz especular
uniform float glossiness;

// intensidad del mapa difuso
uniform float intensidad_difuso;

// intensidad de mapa de relieve
uniform float intensidad_relieve;

const float h = 0.002;

#define M_PI 3.1415926535897932384626433832795

out vec4 FragColor;
void main()
{
	vec3 camera_direction = normalize(position - camera_position);
	// luz unidereccional proveniente del sol
	vec3 light_direction = normalize(vec3(0.37, 0.91, 0.13));
	// calculo de la normal, usando el mapa de normales
	vec3 normalz = normalize(normal);
	vec4 textureNormal = texture(normal_map, TexCoord) * 2 - vec4(1.0,1.0,1.0,1.0);

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

	vec4 TextureColor = texture( diffuse_map, TexCoord ) * intensidad_difuso;
	FragColor = vec4(
		(ka + kd * id) * TextureColor[0] + ks * is,
		(ka + kd * id) * TextureColor[1] + ks * is,
		(ka + kd * id) * TextureColor[2] + ks * is,
		1.0);
}