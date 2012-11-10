#include "stdafx.h"
#include "cubo_texturado_suciedad.h"

CuboTexturadoSuciedad::CuboTexturadoSuciedad(
	Texture* tex,
	Texture* dirtmap,
	CuboTexturado::Cara* caras,
	float _suciedad
	) : Cubo(), texture(tex), mapa_suciedad(dirtmap), suciedad(_suciedad) {
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
	
    glEnableVertexAttribArray(lastIndex());
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), this->extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( lastIndex(), 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	this->dirtnessShader = DirtnessShader::instance();
}

void CuboTexturadoSuciedad::cambiar_suciedad(float _suciedad) {
	this->suciedad = _suciedad;
}

void CuboTexturadoSuciedad::dibujar(const glm::mat4& m) {
	this->dirtnessShader->use();

	texture->load(0);
	mapa_suciedad->load(1);

	dirtnessShader->setTextureUnit(0);
	dirtnessShader->setDirtmapUnit(1);
	dirtnessShader->setDirtlevel(this->suciedad);
	dirtnessShader->setTransformMatrix(m);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, 36);
}
