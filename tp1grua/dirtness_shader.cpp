#include "stdafx.h"
#include "dirtness_shader.h"
#include "glm/ext.hpp"

DirtnessShader::DirtnessShader(const std::string& fragShader, const std::string& vertexShader) : 
	Shader(fragShader, vertexShader) { 
	this->bindAttribLocation(0, "VertexPosition" );
	this->bindAttribLocation(1, "VertexNormal" );
    this->bindAttribLocation(2, "VertexTexCoord" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->dirtmap_location = this->getUniformLocation("suciedad");
	this->dirtlevel_location = this->getUniformLocation("nivel_suciedad");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
	this->projection_matrix_index = this->getUniformLocation("ProjectionMatrix");
	this->camera_direction_index = this->getUniformLocation("camera_direction");
	this->normal_matrix_index = this->getUniformLocation("NormalMatrix");
}

void DirtnessShader::setCameraDirection(const glm::vec3& v) {
	glUniform3f(this->camera_direction_index, v[0], v[1], v[2]);
}

void DirtnessShader::setProjectionMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->projection_matrix_index, 1, 0, glm::value_ptr(m));
}

void DirtnessShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
	glUniformMatrix3fv(this->normal_matrix_index, 1, 0, glm::value_ptr(compute_normal_matrix(m)));
}

void DirtnessShader::setTextureUnit(int unitnumber) {
	glUniform1i(this->texture_location, unitnumber);
}

void DirtnessShader::setDirtmapUnit(int unitnumber) {
	glUniform1i(this->dirtmap_location, unitnumber);
}

void DirtnessShader::setDirtlevel(float level) {
	glUniform1f(this->dirtlevel_location, level);
}

DirtnessShader* DirtnessShader::instance() {
	static DirtnessShader _instance("DirtnessShader.frag", "TextureVShader.vert");
	return &_instance;
}
