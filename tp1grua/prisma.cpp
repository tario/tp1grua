#include "stdafx.h"
#include "prisma.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"

static GLuint construirPoligono(float z, int caras) {
	GLuint vboHandles[20];
    glGenBuffers(4, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint texCoordBufferHandle = vboHandles[1];
    GLuint normalBufferHandle = vboHandles[2];
    GLuint normalxBufferHandle = vboHandles[3];

	int cantidadVertices = caras+2;

	float* vertexdata = new float[cantidadVertices*3];
	float* texcoord_data = new float[cantidadVertices*2];
	float* normaldata = new float[cantidadVertices*3];
	float* normalxdata = new float[cantidadVertices*3];

	glm::vec4 esquina = glm::vec4(0.5, 0.0, z, 1.0);
	glm::mat4 girar = glm::rotate(glm::mat4(1.0), (float)360.0/caras, glm::vec3(0.0,0.0,1.0));

	// el primer vertice, siempre el centro
	vertexdata[0] = 0.0;
	vertexdata[1] = 0.0;
	vertexdata[2] = z;

	texcoord_data[0] = (z>0.0? 0.25 : 0.75);
	texcoord_data[1] = 0.25;

	normaldata[0] = 0.0;
	normaldata[1] = 0.0;
	normaldata[2] = z>0.0 ? 1.0 : -1.0;

	normalxdata[0] = z>0.0 ? 1.0 : -1.0;
	normalxdata[1] = 0.0;
	normalxdata[2] = 0.0;

	for (int i=1; i<cantidadVertices; i++) {
		// despues cada vertice son los giros
		vertexdata[i*3] = esquina[0];
		vertexdata[i*3+1] = esquina[1];
		vertexdata[i*3+2] = esquina[2];

		normaldata[i*3] = 0.0;
		normaldata[i*3+1] = 0.0;
		normaldata[i*3+2] = z>0.0 ? 1.0 : -1.0;

		if (z>0.0) {
			texcoord_data[i*2] = esquina[0] * 0.5 + 0.25;
			texcoord_data[i*2+1] = esquina[1] * 0.5 + 0.25;

			normalxdata[i*3] = 1.0;
			normalxdata[i*3+1] = 0.0;
			normalxdata[i*3+2] = 0.0;
		} else {
			texcoord_data[i*2] = -esquina[0] * 0.5 + 0.75;
			texcoord_data[i*2+1] = -esquina[1] * 0.5 + 0.25;

			normalxdata[i*3] = -1.0;
			normalxdata[i*3+1] = 0.0;
			normalxdata[i*3+2] = 0.0;
		}

		esquina = girar * esquina;
	}
	
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, texCoordBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*2 * sizeof (float), texcoord_data, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normalxdata, GL_STATIC_DRAW );

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
	glBindBuffer( GL_ARRAY_BUFFER, texCoordBufferHandle);
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(3);
	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle);
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] texcoord_data;
	delete[] normaldata;
	delete[] normalxdata;
	delete[] vertexdata;

	return vaoHandle;
}

static GLuint construirCostado(int caras) {
	GLuint vboHandles[20];
    glGenBuffers(4, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint texCoordBufferHandle = vboHandles[1];
    GLuint normalBufferHandle = vboHandles[2];
    GLuint normalxBufferHandle = vboHandles[3];

	int cantidadVertices = caras*2+2;

	float* vertexdata = new float[cantidadVertices*3];
	float* texcoord_data = new float[cantidadVertices*2];
	float* normaldata = new float[cantidadVertices*3];
	float* normalxdata = new float[cantidadVertices*3];

	glm::vec4 esquina = glm::vec4(0.5, 0.0, -0.5, 1.0);
	glm::mat4 girar = glm::rotate(glm::mat4(1.0), (float)360.0/caras, glm::vec3(0.0,0.0,1.0));
	glm::mat4 giroz90 = glm::rotate(glm::mat4(1.0), (float)-90.0, glm::vec3(0.0,0.0,1.0));

	for (int i=0; i<caras+1; i++) {
		// despues cada vertice son los giros
		vertexdata[i*6] = esquina[0];
		vertexdata[i*6+1] = esquina[1];
		vertexdata[i*6+2] = esquina[2];
		vertexdata[i*6+3] = esquina[0];
		vertexdata[i*6+4] = esquina[1];
		vertexdata[i*6+5] = esquina[2]+1.0;

		glm::vec3 vertex_normal = glm::normalize(
				glm::vec3(esquina[0], esquina[1], 0.0)
			);

		normaldata[i*6] = vertex_normal[0];
		normaldata[i*6+1] = vertex_normal[1];
		normaldata[i*6+2] = vertex_normal[2];
		normaldata[i*6+3] = vertex_normal[0];
		normaldata[i*6+4] = vertex_normal[1];
		normaldata[i*6+5] = vertex_normal[2];

		texcoord_data[i*4] = float(i)/float(caras);
		texcoord_data[i*4+1] = 1.0;
		texcoord_data[i*4+2] = float(i)/float(caras);
		texcoord_data[i*4+3] = 0.5;

		glm::vec4 vertex_normalx = giroz90*glm::vec4(vertex_normal,1.0);

		normalxdata[i*6] = vertex_normalx[0];
		normalxdata[i*6+1] = vertex_normalx[1];
		normalxdata[i*6+2] = vertex_normalx[2];
		normalxdata[i*6+3] = vertex_normalx[0];
		normalxdata[i*6+4] = vertex_normalx[1];
		normalxdata[i*6+5] = vertex_normalx[2];

		esquina = girar * esquina;
	}
	
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, texCoordBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*2 * sizeof (float), texcoord_data, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normalxdata, GL_STATIC_DRAW );

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
	glBindBuffer( GL_ARRAY_BUFFER, texCoordBufferHandle);
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(3);
	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle);
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] texcoord_data;
	delete[] normaldata;
	delete[] normalxdata;
	delete[] vertexdata;

	return vaoHandle;
}

Prisma::Prisma(Material* material, int n) :
	material(material) {
	// instanciar los buffers de vertices requeridos para el prisma
	this->caras = n;

	// construir el poligono de la cara superior y de la cara inferior
	this->carasCostado = construirCostado(this->caras);
	this->caraSuperior = construirPoligono(0.5, this->caras);
	this->caraInferior = construirPoligono(-0.5, this->caras);

}

void Prisma::dibujar(const glm::mat4& m) {
	this->material->use(m);

	glBindVertexArray( this->caraSuperior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras+2);

	glBindVertexArray( this->caraInferior );
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->caras+2);

	glBindVertexArray( this->carasCostado );
	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->caras*2+2);
}