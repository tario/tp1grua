#include "stdafx.h"
#include "cubo_texturado.h"

CuboTexturado::CuboTexturado(Texture& texture) : Cubo() {
	this->extra_data = new float[36*2];
}

void CuboTexturado::dibujar() {

}

GLuint CuboTexturado::extraVertexInfo() {
	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);
	
    glEnableVertexAttribArray(1);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), this->extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	return textureCoordBufferHandle;
}
