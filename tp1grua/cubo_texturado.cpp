#include "stdafx.h"
#include "cubo_texturado.h"

CuboTexturado::CuboTexturado(Texture* tex, Cara* caras, bool _carasuperior) : 
	Cubo(_carasuperior), 
	carasuperior(_carasuperior), 
	texture(tex) {
	this->extra_data = new float[36*2];
	int i;

	for (i=0; i<6; i++) {
		extra_data[i*12] = caras[i].coords[0];
		extra_data[i*12+1] = caras[i].coords[1];

		extra_data[i*12+2] = caras[i].coords[2];
		extra_data[i*12+3] = caras[i].coords[3];

		extra_data[i*12+4] = caras[i].coords[6];
		extra_data[i*12+5] = caras[i].coords[7];

		extra_data[i*12+6] = caras[i].coords[2];
		extra_data[i*12+7] = caras[i].coords[3];

		extra_data[i*12+8] = caras[i].coords[6];
		extra_data[i*12+9] = caras[i].coords[7];

		extra_data[i*12+10] = caras[i].coords[4];
		extra_data[i*12+11] = caras[i].coords[5];
	}

	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);
	
    glEnableVertexAttribArray(Cubo::lastIndex);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), this->extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( Cubo::lastIndex, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	textureShader = TextureShader::instance();
}

void CuboTexturado::dibujar(const glm::mat4& m) {
	this->textureShader->use();

	texture->load(0);
	textureShader->setTextureUnit(0);
	textureShader->setTransformMatrix(m);

	glBindVertexArray( this->getVaoHandle() );
	if (carasuperior) {
	glDrawArrays( GL_TRIANGLES, 0, 36); 
	} else {
	glDrawArrays( GL_TRIANGLES, 0, 30); 
	}
}
