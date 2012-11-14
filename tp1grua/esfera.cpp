#include "stdafx.h" 
#include "esfera.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>


static void assignvec3(float* data, glm::vec4 vect) {
	data[0] = glm::vec3(vect)[0];
	data[1] = glm::vec3(vect)[1];
	data[2] = glm::vec3(vect)[2];
}

static glm::vec4 getvec4(float* data) {
	return glm::vec4(data[0],data[1],data[2],1.0);
}

Esfera::Esfera(Material* material, int geometric_detail) : material(material) {
	GLuint vboHandles[3];
    glGenBuffers(2, vboHandles);

    GLuint positionBufferHandle = vboHandles[0];
    GLuint normalBufferHandle = vboHandles[1];


	int cantidadVerticesMeridiano = (geometric_detail-2)*6 + 6;
	this->cantidadVertices = cantidadVerticesMeridiano*geometric_detail;

	float* vertexdata = new float[cantidadVertices*3];
	float* normaldata = new float[cantidadVertices*3];

	glm::mat4 girox = glm::rotate(glm::mat4(1.0), 180.0f / geometric_detail, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 girox_contrario = glm::rotate(glm::mat4(1.0), -180.0f / geometric_detail, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 giroz = glm::rotate(glm::mat4(1.0), 360.0f / geometric_detail, glm::vec3(0.0, 0.0, 1.0));

	float* indiceMeridiano = vertexdata;
	
	glm::vec4 currentPoint = girox * glm::vec4(0.0,0.0,0.5,1.0);
	assignvec3(indiceMeridiano, glm::vec4(0.0,0.0,0.5,1.0));
	assignvec3(indiceMeridiano+3, currentPoint);
	assignvec3(indiceMeridiano+6, giroz * currentPoint);
	assignvec3(indiceMeridiano+9, giroz * girox_contrario * glm::vec4(0.0,0.0,-0.5,1.0));
	assignvec3(indiceMeridiano+12, girox_contrario * glm::vec4(0.0,0.0,-0.5,1.0));
	assignvec3(indiceMeridiano+15, glm::vec4(0.0,0.0,-0.5,1.0));

	for (int i=1; i<geometric_detail-1; i++){
		glm::vec4 nextPoint = girox * currentPoint;

		assignvec3(indiceMeridiano+i*18, currentPoint);
		assignvec3(indiceMeridiano+i*18+3, nextPoint);
		assignvec3(indiceMeridiano+i*18+6, giroz * nextPoint);
		assignvec3(indiceMeridiano+i*18+9, currentPoint);
		assignvec3(indiceMeridiano+i*18+12, giroz * currentPoint);
		assignvec3(indiceMeridiano+i*18+15, giroz * nextPoint);

		currentPoint = nextPoint;
	}

	for (int j=1; j<geometric_detail; j++) {
		indiceMeridiano = vertexdata + j*cantidadVerticesMeridiano*3;
		giroz = glm::rotate(glm::mat4(1.0), j * 360.0f / geometric_detail, glm::vec3(0.0, 0.0, 1.0));

		for (int i=0; i<cantidadVerticesMeridiano; i++){
			assignvec3(indiceMeridiano+i*3, giroz * getvec4(vertexdata+i*3));
		}
	}

	for (int i=0; i<cantidadVertices; i++) {
		assignvec3(normaldata+i*3, glm::normalize(getvec4(vertexdata+i*3)));
	}

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW );

    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

	glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] vertexdata;
	delete[] normaldata;
}

void Esfera::dibujar(const glm::mat4& m) {
	material->use(m);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, cantidadVertices); 
}
