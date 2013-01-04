#include "stdafx.h"
#include "target_quad.h"

static void assignvec3(float* data, float x, float y, float z) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

TargetQuad::TargetQuad() : material(glm::vec3(0.0,1.0,0.0)) {
    glGenVertexArrays( 1, &this->vaoHandle );
    glBindVertexArray( this->vaoHandle );

	float vertexdata[15];
	float normaldata[15];
	GLuint positionBufferHandle;
	glGenBuffers(1, &positionBufferHandle);
	GLuint normalBufferHandle;
	glGenBuffers(1, &normalBufferHandle);
	float l=0.5;
	assignvec3(vertexdata, 0.0, l, l);
	assignvec3(vertexdata+3, 0.0, l, -l);
	assignvec3(vertexdata+6, 0.0, -l, -l);
	assignvec3(vertexdata+9, 0.0, -l, l);

	assignvec3(normaldata, l, -l, 0.0);
	assignvec3(normaldata+3, l, l, 0.0);
	assignvec3(normaldata+6, -l, l, 0.0);
	assignvec3(normaldata+9, -l, -l, 0.0);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 4*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );
    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 4*3 * sizeof (float), normaldata, GL_STATIC_DRAW );
    // Enable the vertex attributes array
    glEnableVertexAttribArray(1);

    // Map index 1 to the normal buffer
    glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}
void TargetQuad::dibujar(const glm::mat4& m) {
	material.use(m);

	glBindVertexArray( this->vaoHandle );
	glDrawArrays(GL_LINE_LOOP,0, 4);

	//cuboTexturado.dibujar(m);
}
