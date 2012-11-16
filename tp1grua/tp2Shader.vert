#version 330

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;
uniform mat4 TransformMatrix;

out vec2 TexCoord;
out vec3 normal; 
out vec3 position;

void main()
{
		TexCoord = VertexTexCoord;
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		normal = NormalMatrix * VertexNormal;
		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);
		position = vec3(trVertexPosition[0], trVertexPosition[1], trVertexPosition[2]);
}