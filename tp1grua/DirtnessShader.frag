#version 330
in vec2 TexCoord;
in float light_intensity;
in vec3 normal;
in vec3 light_direction;

uniform sampler2D texture1;
uniform sampler2D suciedad;
uniform float nivel_suciedad;

out vec4 FragColor;

void main()
{

	   float range = texture( suciedad, TexCoord )[0] * nivel_suciedad + 1.0 - nivel_suciedad;
	   FragColor = light_intensity * texture( texture1, TexCoord ) * range;
//	FragColor = vec4(normalize(reflected),1.0);
}