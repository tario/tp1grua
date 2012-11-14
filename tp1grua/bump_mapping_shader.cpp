#include "stdafx.h"
#include "bump_mapping_shader.h"
#include "glm/ext.hpp"

BumpMappingShader::BumpMappingShader() : Shader("BumpMappingFShader.frag", "TextureVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
	this->bindAttribLocation(1, "VertexNormal" );
	this->bindAttribLocation(2, "VertexTexCoord" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
	this->camera_direction_index = this->getUniformLocation("camera_direction");
	this->normal_matrix_index = this->getUniformLocation("NormalMatrix");
	this->ka_index = this->getUniformLocation("ka");
	this->kd_index = this->getUniformLocation("kd");
	this->ks_index = this->getUniformLocation("ks");
	this->normal_map_index = this->getUniformLocation("normalmap");
}

void BumpMappingShader::setLightningParameters(float ka, float kd, float ks) {
	glUniform1f(this->ka_index, ka);
	glUniform1f(this->kd_index, kd);
	glUniform1f(this->ks_index, ks);
}

void BumpMappingShader::setCameraDirection(const glm::vec3& v) {
	glUniform3f(this->camera_direction_index, v[0], v[1], v[2]);
}

void BumpMappingShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

void BumpMappingShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
	glUniformMatrix3fv(this->normal_matrix_index, 1, 0, glm::value_ptr(compute_normal_matrix(m)));
}

void BumpMappingShader::setTextureUnit(int unitnumber) {
	glUniform1i(this->texture_location, unitnumber);
}

void BumpMappingShader::setNormalmapUnit(int unitnumber) {
	glUniform1i(this->normal_map_index, unitnumber);
}

BumpMappingShader* BumpMappingShader::instance() {
	static BumpMappingShader _instance;
	return &_instance;
}
