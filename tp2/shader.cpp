#include "stdafx.h"
#include "shader.h"
#include <iostream>
#include <fstream>


glm::mat4 Shader::projectionMatrix;
glm::vec3 Shader::cameraDirection;
glm::vec3 Shader::cameraPosition;
	// carga un programa dadas las rutas del shader de fragmento y shader de vertices
Shader::Shader(ShaderProgram* shaderProgram) : shaderProgram(shaderProgram) {

}

void Shader::ConcreteSetter<int>::apply() {
	glUniform1i(index, x);
}

void Shader::ConcreteSetter<float>::apply() {
	glUniform1f(index, x);
}

void Shader::ConcreteSetter<glm::mat4>::apply() {
	glUniformMatrix4fv(index, 1, 0, glm::value_ptr(x));
}

void Shader::ConcreteSetter<glm::mat3>::apply() {
	glUniformMatrix3fv(index, 1, 0, glm::value_ptr(x));
}

void Shader::ConcreteSetter<glm::vec3>::apply() {
	glUniform3f(index, x[0], x[1], x[2]);
}

float Shader::ConcreteSetter<float>::get() {
	return x;
}
void Shader::use() {
	shaderProgram->use();

	for (std::vector<Setter*>::iterator it = setters.begin();
		it != setters.end(); it++) {
		(*it)->apply();
	}
}

glm::mat4 Shader::compute_normal_matrix(const glm::mat4& m) {
	return glm::transpose(glm::inverse(m));
}

