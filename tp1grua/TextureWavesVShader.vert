#version 330

in vec3 VertexPosition;
in vec3 Neighbor1;
in vec3 Neighbor2;
in vec2 VertexTexCoord;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;
uniform float fase;
uniform float fase2;

out vec2 TexCoord;
out vec3 normal;

void main()
{
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
		vec4 trNeighbor1 = TransformMatrix * vec4(Neighbor1, 1.0);
		vec4 trNeighbor2 = TransformMatrix * vec4(Neighbor2, 1.0);

        gl_Position = ProjectionMatrix * trVertexPosition; 

		normal = cross(
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor1[0],trNeighbor1[1],trNeighbor1[2]), 
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor2[0],trNeighbor2[1],trNeighbor2[2]));
}