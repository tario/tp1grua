#include "stdafx.h"
#include "curva_bezier.h"

static int factorial(int x){
	if (x <= 1) {
		return 1;
	} else {
		return x * factorial(x-1);
	}
}

static glm::vec3 bezier_eval(const std::vector<glm::vec3>& v, float t) {
	glm::vec3 ret(0.0,0.0,0.0);
	int n=v.size();
	for (int i=0; i<n; i++) {
		float factor = float(factorial(n-1))/float(factorial(i))/float(factorial(n-i-1));
		glm::vec3 punto = v[i];
		if (i==0) {
			ret = ret + punto * factor * float(pow(1.0-t,n-i-1));
		} else if (n-i-1==0) {
			ret = ret + punto * factor * float(pow(t,i));
		} else {
			ret = ret + punto * factor * float(pow(1.0-t,n-i-1) * pow(t,i));
		}
	}

	return ret;
}

static std::vector<glm::vec3> bezier(const std::vector<glm::vec3>& v, int n) {
	std::vector<glm::vec3> ret;

	for (int i=0; i<n; i++) {
		float t = float(i)/float(n);
		ret.push_back(bezier_eval(v,t));
	}
	return ret;
}
	
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
	actualizar_puntos(bezier(v,64));
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
