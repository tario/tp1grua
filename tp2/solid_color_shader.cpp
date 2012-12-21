#include "stdafx.h"
#include "solid_color_shader.h"
#include "glm/ext.hpp"

SolidColorShader::SolidColorShader() {

	this->shader = new ShaderProgram("BasicColorFShader.frag", "BasicColorVShader.vert"); 

	this->shader ->bindAttribLocation(0, "VertexPosition" );
	this->shader ->bindAttribLocation(1, "VertexNormal" );
	this->shader ->link();

	this->transform_matrix_index = this->shader->getUniformLocation("TransformMatrix");
	this->normal_matrix_index = this->shader->getUniformLocation("NormalMatrix");
	this->projection_matrix_index = this->shader->getUniformLocation("ProjectionMatrix");

	this->camera_position_index = this->shader->getUniformLocation("camera_position");
	this->color_index = this->shader->getUniformLocation("Color");
}

void SolidColorShader::setCameraDirection(const glm::vec3& v) {
	glUniform3f(this->camera_direction_index, v[0], v[1], v[2]);
}

void SolidColorShader::setCameraPosition(const glm::vec3& v) {
	glUniform3f(this->camera_position_index, v[0], v[1], v[2]);
}

void SolidColorShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

SolidColorShader* SolidColorShader::instance() {
	static SolidColorShader _instance;
	return &_instance;
}

void SolidColorShader::setColor(const glm::vec3& color) {
	glUniform3f(this->color_index, color[0], color[1], color[2]);
}

void SolidColorShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
	glm::mat4 normal_matrix = Shader::compute_normal_matrix(m);
	glUniformMatrix4fv(this->normal_matrix_index, 1, 0, glm::value_ptr(normal_matrix));
}

