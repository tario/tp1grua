#include "stdafx.h"
#include "texture_waves_shader.h"
#include "glm/ext.hpp"

TextureWavesShader::TextureWavesShader() : Shader("TextureFShader.frag", "TextureWavesVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
    this->bindAttribLocation(1, "VertexNormal" );
    this->bindAttribLocation(2, "VertexTexCoord" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->fase_location = this->getUniformLocation("fase");
	this->fase2_location = this->getUniformLocation("fase2");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
	this->normal_matrix_index = this->getUniformLocation("NormalMatrix");
	this->camera_direction_index = this->getUniformLocation("camera_direction");
	this->ka_index = this->getUniformLocation("ka");
	this->kd_index = this->getUniformLocation("kd");
	this->ks_index = this->getUniformLocation("ks");
}

void TextureWavesShader::setLightningParameters(float ka, float kd, float ks) {
	glUniform1f(this->ka_index, ka);
	glUniform1f(this->kd_index, kd);
	glUniform1f(this->ks_index, ks);
}

void TextureWavesShader::setCameraDirection(const glm::vec3& v) {
	glUniform3f(this->camera_direction_index, v[0], v[1], v[2]);
}

void TextureWavesShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

void TextureWavesShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
	glUniformMatrix3fv(this->normal_matrix_index, 1, 0, glm::value_ptr(compute_normal_matrix(m)));
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
