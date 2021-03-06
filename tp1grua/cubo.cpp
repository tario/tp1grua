#include "stdafx.h"
#include "cubo.h"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

static void assignvec3(float* data, glm::vec4 vect) {
	data[0] = glm::vec3(vect)[0];
	data[1] = glm::vec3(vect)[1];
	data[2] = glm::vec3(vect)[2];
}

static void square(float* data, glm::mat4 matrix) {
	float l = 0.5;
	assignvec3(data, matrix * glm::vec4(l, -l, -l, 1.0f));
	assignvec3(data+3, matrix * glm::vec4(l, -l, l, 1.0f));
	assignvec3(data+6, matrix * glm::vec4(l, l, -l, 1.0f));
	assignvec3(data+9, matrix * glm::vec4(l, -l, l, 1.0f));
	assignvec3(data+12, matrix * glm::vec4(l, l, -l, 1.0f));
	assignvec3(data+15, matrix * glm::vec4(l, l, l, 1.0f));
}

Cubo::Cubo(bool carasuperior) {
	float vertexdata[36*3];
	GLuint positionBufferHandle;

	glGenBuffers(1, &positionBufferHandle);

	glm::mat4 reflection = glm::scale(glm::vec3(1.0,1.0,-1.0));
	glm::mat4 yrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 zrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(0.0f,0.0f,1.0f));
	square(vertexdata, glm::mat4(1.0));
	square(vertexdata+6*3, zrotation);
	square(vertexdata+12*3, zrotation * zrotation);
	square(vertexdata+18*3, zrotation * zrotation * zrotation);
	square(vertexdata+24*3, yrotation);
	if (carasuperior) square(vertexdata+30*3, yrotation  * yrotation * yrotation);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
	if (carasuperior) {
    glBufferData( GL_ARRAY_BUFFER, 36*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );
	} else {
    glBufferData( GL_ARRAY_BUFFER, 30*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );
	}

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &this->vaoHandle );
    glBindVertexArray( this->vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}
