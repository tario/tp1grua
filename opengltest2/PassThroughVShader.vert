#version 330

in vec3 VertexPosition;
in vec3 VertexColor;

uniform mat4 TransformMatrix;

out vec3 Color;

void main()
{
        Color = VertexColor;
        gl_Position = TransformMatrix * vec4( VertexPosition, 1.0);
}