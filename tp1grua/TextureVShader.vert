#version 330

in vec3 VertexPosition;
in vec3 Neighbor1;
in vec3 Neighbor2;
in vec2 VertexTexCoord;

uniform mat4 TransformMatrix;

out vec2 TexCoord;
out vec3 normal;

void main()
{
        TexCoord = VertexTexCoord;
        gl_Position = TransformMatrix * vec4( VertexPosition, 1.0);
		vec4 trNeighbor1 = TransformMatrix * vec4(Neighbor1, 1.0);
		vec4 trNeighbor2 = TransformMatrix * vec4(Neighbor2, 1.0);
		normal = cross(
			vec3(gl_Position[0],gl_Position[1],gl_Position[2]) - vec3(Neighbor1[0],Neighbor1[1],Neighbor1[2]), 
			vec3(gl_Position[0],gl_Position[1],gl_Position[2]) - vec3(Neighbor2[0],Neighbor2[1],Neighbor2[2]));
}