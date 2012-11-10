#include "stdafx.h"
#include "texture_waves_shader.h"
#include "glm/ext.hpp"

TextureWavesShader::TextureWavesShader() : Shader("TextureFShader.frag", "TextureWavesVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
    this->bindAttribLocation(1, "VertexColor" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->fase_location = this->getUniformLocation("fase");
	this->fase2_location = this->getUniformLocation("fase2");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
}

void TextureWavesShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

void TextureWavesShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
}

void TextureWavesShader::setTextureUnit(int unitnumber) {
	glUniform1i(this->texture_location, unitnumber);
}

void TextureWavesShader::setFase(float fase) {
	glUniform1f(this->fase_location, fase);
}

void TextureWavesShader::setFase2(float fase2) {
	glUniform1f(this->fase2_location, fase2);
}

TextureWavesShader* TextureWavesShader::instance() {
	static TextureWavesShader _instance;
	return &_instance;
}
