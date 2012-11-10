#include "stdafx.h"
#include "olas.h" 

static const int filas = 100;
static const int celdas = 100;
static const int cantidadVertices = filas * (celdas+1) * 2;

Olas::Olas(Texture* _texture) : texture(_texture) {
	float vertexdata[cantidadVertices*3];
	float extra_data[cantidadVertices*2];

	GLuint positionBufferHandle;
	int i, j;
	int index = 0;
	for (i=0; i<filas; i++) {
		for (j=0; j<celdas+1; j++) {
			vertexdata[index*3] = -0.5 + (float)i * (float)1.0/(float)filas;
			vertexdata[index*3+1] = -0.5 + (float)j * (float)1.0/(float)celdas;
			vertexdata[index*3+2] = 0.5;
			vertexdata[index*3+3] = vertexdata[index*3] + (float)1.0/(float)filas; 
			vertexdata[index*3+4] = vertexdata[index*3+1];
			vertexdata[index*3+5] = 0.5;
			index = index + 2;
		}
	}

	glGenBuffers(1, &positionBufferHandle);

	glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &this->vaoHandle );
    glBindVertexArray( this->vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	for (i=0; i<cantidadVertices; i++) {
		extra_data[i*2] = (vertexdata[i*3]+0.5)*10.0;
		extra_data[i*2+1] = (vertexdata[i*3+1]+0.5)*10.0;
	}

	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);
	
    glEnableVertexAttribArray(1);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, cantidadVertices*2 * sizeof (float), extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	textureWavesShader = TextureWavesShader::instance();
}

static float t=0.0;
static float t2=0.0;
void Olas::dibujar(const glm::mat4& m) {
	this->textureWavesShader->use();
	this->textureWavesShader->setFase(t);
	this->textureWavesShader->setFase2(t2);
	t = t + 0.07;
	if (t<0) t+=6.28;
	t2 = t2 - 0.11;
	if (t2<0) t2+=6.28;
	texture->load(0);
	textureWavesShader->setTextureUnit(0);
	textureWavesShader->setTransformMatrix(m);
	textureWavesShader->setProjectionMatrix(Shader::projectionMatrix);

	glBindVertexArray( this->vaoHandle );
	for (int i=0; i<filas; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP,i*(celdas+1)*2,(celdas+1)*2);
	}
}
