#include "stdafx.h"
#include "color_shader.h"
#include "glm/ext.hpp"

ColorShader::ColorShader() : Shader("BasicFShader.frag", "PassThroughVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
    this->bindAttribLocation(1, "VertexColor" );
	this->link();

	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
}

ColorShader* ColorShader::instance() {
	static ColorShader _instance;
	return &_instance;
}

void ColorShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
}

