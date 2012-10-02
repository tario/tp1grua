#include "stdafx.h"
#include "prisma.h"

static GLuint construirPoligono(float z, int caras, glm::vec3 color) {
	GLuint vboHandles[20];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

	int cantidadVertices = caras+1;

	float* vertexdata = new float[cantidadVertices*3];
	float* colordata = new float[cantidadVertices*3];

	for (int i=0; i++; i<cantidadVertices) {
		colordata[i*3] = color[0];
		colordata[i*3+1] = color[1];
		colordata[i*3+2] = color[2];
	}

	glm::vec4 esquina = glm::vec4(0.5, 0.0, z, 1.0);
	glm::mat4 girar = glm::rotate(glm::mat4(1.0), (float)360.0/caras, glm::vec3(0.0,0.0,1.0));

	// el primer vertice, siempre el centro
	vertexdata[0] = 0.0;
	vertexdata[1] = 0.0;
	vertexdata[2] = z;

	for (int i=1; i++; i<cantidadVertices) {
		// despues cada vertice son los giros
		vertexdata[i*3] = esquina[0];
		vertexdata[i*3+1] = esquina[1];
		vertexdata[i*3+2] = esquina[2];

		esquina = girar * esquina;
	}

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), colordata, GL_STATIC_DRAW );

	GLuint vaoHandle;
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] colordata;
	delete[] vertexdata;

	return vaoHandle;
}

Prisma::Prisma(int n, glm::vec3 color) {
	// instanciar los buffers de vertices requeridos para el prisma
	this->caras = n;

	// construir el poligono de la cara superior y de la cara inferior
	this->caraSuperior = construirPoligono(0.5, n, color);
	this->caraInferior = construirPoligono(-0.5, n, color);
}

void Prisma::dibujar(const glm::mat4& m) {
	glBindVertexArray( this->caraSuperior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras*2);

	glBindVertexArray( this->caraInferior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras*2);
}