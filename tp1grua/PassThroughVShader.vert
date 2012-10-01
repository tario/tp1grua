#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoord;

uniform mat4 TransformMatrix;

out vec2 TexCoord;

void main()
{
        TexCoord = VertexTexCoord;
        gl_Position = TransformMatrix * vec4( VertexPosition, 1.0);
}