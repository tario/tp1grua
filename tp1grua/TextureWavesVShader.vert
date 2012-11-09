#version 330

in vec3 VertexPosition;
in vec3 Neighbor1;
in vec3 Neighbor2;
in vec2 VertexTexCoord;

uniform mat4 TransformMatrix;
uniform float fase;
uniform float fase2;

out vec2 TexCoord;

void main()
{
        TexCoord = VertexTexCoord;
		float t = VertexPosition[0]*20.0 + fase + VertexPosition[1]*VertexPosition[1];
		float t2 = VertexPosition[0]*50.0 + fase2 + VertexPosition[1]*3.0 + VertexPosition[1]*VertexPosition[1]*0.7;
		float a = 0.4 * (VertexPosition[0]+0.5);
		float b = 0.15 * (0.5 - VertexPosition[0]);
        gl_Position = TransformMatrix * 
			vec4( 
				VertexPosition[0], 
				VertexPosition[1], 
				VertexPosition[2]+a*sin(t) + b*sin(t2), 
				1.0);
}