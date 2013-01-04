#version 330

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;
in vec3 VertexNormalX;

uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;
uniform mat4 TransformMatrix;

out vec2 TexCoord;
out vec3 normal; 
out vec3 position;
out vec3 normalx; 

void main()
{
		TexCoord = VertexTexCoord;
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		
		vec4 normal4 = NormalMatrix * vec4(VertexNormal,1.0);
		normal = vec3(normal4[0], normal4[1], normal4[2]);

		normal4 = NormalMatrix * vec4(VertexNormalX,1.0);
		normalx = vec3(normal4[0], normal4[1], normal4[2]);

		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);
		position = vec3(trVertexPosition[0], trVertexPosition[1], trVertexPosition[2]);
}