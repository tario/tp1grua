#version 330

in vec2 TexCoord;
uniform sampler2D texture1;

out vec4 FragColor;

void main()
{
       // FragColor = vec4( 0.5, 0.5, 0.5, 1.0) ;
	   FragColor = texture( texture1, TexCoord );
}