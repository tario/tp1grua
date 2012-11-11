#version 330

in vec3 VertexPosition;
in vec3 Neighbor1;
in vec3 Neighbor2;
in vec2 VertexTexCoord;

uniform mat4 ProjectionMatrix;
uniform mat4 TransformMatrix;

out vec2 TexCoord;
out vec3 normal; 
out vec3 position;

void main()
{
		TexCoord = VertexTexCoord;
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		vec4 trNeighbor1 = TransformMatrix * vec4(Neighbor1, 1.0);
		vec4 trNeighbor2 = TransformMatrix * vec4(Neighbor2, 1.0);

		normal = cross(
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor1[0],trNeighbor1[1],trNeighbor1[2]), 
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor2[0],trNeighbor2[1],trNeighbor2[2]));

		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);

		position = vec3(trVertexPosition[0], trVertexPosition[1], trVertexPosition[2]);
}