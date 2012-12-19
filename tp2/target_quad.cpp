#include "stdafx.h"
#include "target_quad.h"

static void assignvec3(float* data, float x, float y, float z) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
}
static float cara2[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
static CuboTexturado::Cara caras2[] = {
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2)
};

TargetQuad::TargetQuad() : material(glm::vec3(1.0,0.0,0.0)), cuboTexturado(&material, caras2) {
    glGenVertexArrays( 1, &this->vaoHandle );
    glBindVertexArray( this->vaoHandle );

	float vertexdata[15];
	GLuint positionBufferHandle;
	glGenBuffers(1, &positionBufferHandle);
	float l=0.5;
	assignvec3(vertexdata, 0.0, l, l);
	assignvec3(vertexdata+3, 0.0, l, -l);
	assignvec3(vertexdata+6, 0.0, -l, -l);
	assignvec3(vertexdata+9, 0.0, -l, l);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 4*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );
    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}
void TargetQuad::dibujar(const glm::mat4& m) {
	material.use(m);

	glBindVertexArray( this->vaoHandle );
	glDrawArrays(GL_LINE_LOOP,0, 4);

	//cuboTexturado.dibujar(m);
}
