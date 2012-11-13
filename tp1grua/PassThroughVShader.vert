#version 330

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec3 VertexColor;

uniform mat4 TransformMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

out vec3 Color;
out vec3 normal;
out vec3 position;

void main()
{		
        Color = VertexColor;
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		normal = NormalMatrix * VertexNormal;
		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);
		position = vec3(trVertexPosition[0], trVertexPosition[1], trVertexPosition[2]);
}