#include "stdafx.h"
#include "prisma.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"

static GLuint construirPoligono(float z, int caras, glm::vec3 color) {
	GLuint vboHandles[20];
    glGenBuffers(3, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    GLuint normalBufferHandle = vboHandles[2];

	int cantidadVertices = caras+2;

	float* vertexdata = new float[cantidadVertices*3];
	float* colordata = new float[cantidadVertices*3];
	float* normaldata = new float[cantidadVertices*3];

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

	for (int i=1; i<cantidadVertices; i++) {
		// despues cada vertice son los giros
		vertexdata[i*3] = esquina[0];
		vertexdata[i*3+1] = esquina[1];
		vertexdata[i*3+2] = esquina[2];

		normaldata[i*3] = 0.0;
		normaldata[i*3+1] = 0.0;
		normaldata[i*3+2] = z>0.0 ? 1.0 : -1.0;

		esquina = girar * esquina;
	}
	
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW);

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), colordata, GL_STATIC_DRAW );

	GLuint vaoHandle;
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] colordata;
	delete[] vertexdata;

	return vaoHandle;
}

static GLuint construirCostado(int caras, glm::vec3 color) {
	GLuint vboHandles[20];
    glGenBuffers(3, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    GLuint normalBufferHandle = vboHandles[2];

	int cantidadVertices = caras*2+2;

	float* vertexdata = new float[cantidadVertices*3];
	float* colordata = new float[cantidadVertices*3];
	float* normaldata = new float[cantidadVertices*3];
	
	for (int i=0; i<cantidadVertices; i++) {
		colordata[i*3] = color[0];
		colordata[i*3+1] = color[1];
		colordata[i*3+2] = color[2];
	}

	glm::vec4 esquina = glm::vec4(0.5, 0.0, -0.5, 1.0);
	glm::mat4 girar = glm::rotate(glm::mat4(1.0), (float)360.0/caras, glm::vec3(0.0,0.0,1.0));

	for (int i=0; i<caras+1; i++) {
		// despues cada vertice son los giros
		vertexdata[i*6] = esquina[0];
		vertexdata[i*6+1] = esquina[1];
		vertexdata[i*6+2] = esquina[2];
		vertexdata[i*6+3] = esquina[0];
		vertexdata[i*6+4] = esquina[1];
		vertexdata[i*6+5] = esquina[2]+1.0;

		glm::vec3 vertex_normal = glm::normalize(
				glm::vec3(esquina[0], esquina[1], esquina[2])
			);

		normaldata[i*6] = vertex_normal[0];
		normaldata[i*6+1] = vertex_normal[1];
		normaldata[i*6+2] = vertex_normal[2];
		normaldata[i*6+3] = vertex_normal[0];
		normaldata[i*6+4] = vertex_normal[1];
		normaldata[i*6+5] = vertex_normal[2];

		esquina = girar * esquina;
	}
	
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), colordata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW );

	GLuint vaoHandle;
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] colordata;
	delete[] normaldata;
	delete[] vertexdata;

	return vaoHandle;
}

Prisma::Prisma(glm::vec3 color, int n) {
	// instanciar los buffers de vertices requeridos para el prisma
	this->caras = n;

	// construir el poligono de la cara superior y de la cara inferior
	this->caraSuperior = construirPoligono(0.5, this->caras, color);
	this->caraInferior = construirPoligono(-0.5, this->caras, color);
	this->carasCostado = construirCostado(this->caras, color);

	this->colorShader = ColorShader::instance();
}

void Prisma::dibujar(const glm::mat4& m) {
	this->colorShader->use();
	colorShader->setTransformMatrix(m);
	colorShader->setProjectionMatrix(Shader::projectionMatrix);

	glBindVertexArray( this->caraSuperior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras+2);

	glBindVertexArray( this->caraInferior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras+2);

	glBindVertexArray( this->carasCostado );
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->caras*2+2);
}