#version 330
in vec3 Color;
in float light_intensity;

out vec4 FragColor;
void main()
{
        FragColor = light_intensity * vec4( Color, 1.0) ;
}