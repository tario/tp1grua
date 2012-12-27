#include "stdafx.h"
#include "curva_bezier.h"
#include "bezier.h"

static void assignvec3(float* data, glm::vec3 v) {
	data[0] = v[0];
	data[1] = v[1];
	data[2] = v[2];
}

CurvaBezier::CurvaBezier() : material(glm::vec3(0.0,1.0,0.0),false) {
    glGenVertexArrays( 1, &this->vaoHandle );
    glBindVertexArray( this->vaoHandle );
	glGenBuffers(1, &this->positionBufferHandle);

    glEnableVertexAttribArray(0);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

void CurvaBezier::actualizar_puntos_de_control(const std::vector<glm::vec3>& v) {
	actualizar_puntos(puntos_bezier(v,64));
}

void CurvaBezier::actualizar_puntos(const std::vector<glm::vec3>& v) {
	float *vertexdata = (float*)malloc(sizeof(float)*3*v.size());

	this->cantidadVertices = v.size();
	for (int i=0; i<v.size();i++) {
		assignvec3(vertexdata+i*3, v.at(i));
	}

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, this->cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	free(vertexdata);
}

void CurvaBezier::dibujar(const glm::mat4& m) {
	material.use(m);

	glBindVertexArray( this->vaoHandle );
	glDrawArrays(GL_LINE_STRIP,0, this->cantidadVertices);
}
