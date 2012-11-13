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
out vec3 normal;
out float light_intensity;

void main()
{
		vec3 light_direction;

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
		float x = VertexPosition[0];
		float y = VertexPosition[1];
		normal = -vec3(
			0.4 * sin(20.0*x + fase + y*y) + 0.4*(x + 0.5)*cos(20.0*x+fase + y*y)*20.0 -
			0.15 * sin(50.0*x + fase2 + 3*y + y*y*0.7) + 0.15*(0.5-x)*cos(50*x + fase2 + 3*y + y*y*0.7)*50
			,
			0.4 * (x + 0.5) * cos(20*x + fase + y*y) * 2 * y + 
			0.15 * (0.5 - x) * cos(50*x + fase2 + 3*y + y*y*0.7)*(3+2*y),
			-1.0);
		normal = normalize(normal);
}