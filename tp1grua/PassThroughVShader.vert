#version 330

in vec3 VertexPosition;
in vec3 Neighbor1;
in vec3 Neighbor2;
in vec3 VertexColor;

uniform mat4 TransformMatrix;
uniform mat4 ProjectionMatrix;

out vec3 Color;
out float light_intensity;

void main()
{
		vec3 light_direction;
		vec3 normal;
		
        Color = VertexColor;
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		vec4 trNeighbor1 = TransformMatrix * vec4(Neighbor1, 1.0);
		vec4 trNeighbor2 = TransformMatrix * vec4(Neighbor2, 1.0);
		normal = cross(
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor1[0],trNeighbor1[1],trNeighbor1[2]), 
			vec3(trVertexPosition[0],trVertexPosition[1],trVertexPosition[2]) - vec3(trNeighbor2[0],trNeighbor2[1],trNeighbor2[2]));

		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);

		light_direction = normalize(vec3(10.0, -0.14, -1.0));

		float k1 = max(dot(normalize(light_direction), normalize(normal)), 0.0);
		light_intensity = 0.2 + k1 * 0.8;
}