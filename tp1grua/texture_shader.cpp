#include "stdafx.h"
#include "texture_shader.h"
#include "glm/ext.hpp"

TextureShader::TextureShader() : Shader("TextureFShader.frag", "TextureVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
	this->bindAttribLocation(1, "Neighbor1" );
	this->bindAttribLocation(2, "Neighbor2" );
	this->bindAttribLocation(3, "VertexTexCoord" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
}

void TextureShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

void TextureShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
}

void TextureShader::setTextureUnit(int unitnumber) {
	glUniform1i(this->texture_location, unitnumber);
}

TextureShader* TextureShader::instance() {
	static TextureShader _instance;
	return &_instance;
}
