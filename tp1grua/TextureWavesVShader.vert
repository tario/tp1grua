#version 330

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

uniform mat4 TransformMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform float fase;
uniform float fase2;

out vec2 TexCoord;
out float light_intensity;

void main()
{
		vec3 light_direction;
		vec3 normal;

        TexCoord = VertexTexCoord;
		float t = VertexPosition[0]*20.0 + fase + VertexPosition[1]*VertexPosition[1];
		float t2 = VertexPosition[0]*50.0 + fase2 + VertexPosition[1]*3.0 + VertexPosition[1]*VertexPosition[1]*0.7;
		float a = 0.4 * (VertexPosition[0]+0.5);
		float b = 0.15 * (0.5 - VertexPosition[0]);

		vec4 trVertexPosition = TransformMatrix * 
			vec4( 
				VertexPosition[0], 
				VertexPosition[1], 
				VertexPosition[2]+a*sin(t) + b*sin(t2), 
				1.0);

        gl_Position = ProjectionMatrix * trVertexPosition; 

		normal = vec3(0.0,0.0,1.0);
		light_direction = normalize(vec3(10.0, -0.14, -1.0));

		float k1 = max(dot(normalize(light_direction), normalize(normal)), 0.0);
		light_intensity = 0.2 + k1 * 0.8;
}