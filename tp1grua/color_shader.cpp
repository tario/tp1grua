#include "stdafx.h"
#include "color_shader.h"
#include "glm/ext.hpp"

ColorShader::ColorShader() : Shader("BasicFShader.frag", "PassThroughVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
	this->bindAttribLocation(1, "Neighbor1" );
	this->bindAttribLocation(2, "Neighbor2" );
	this->bindAttribLocation(3, "VertexColor" );
	this->link();

	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
	this->camera_direction_index = this->getUniformLocation("camera_direction");
}

void ColorShader::setCameraDirection(const glm::vec3& v) {
	glUniform3f(this->camera_direction_index, v[0], v[1], v[2]);
}

void ColorShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

ColorShader* ColorShader::instance() {
	static ColorShader _instance;
	return &_instance;
}

void ColorShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
}

