#include "stdafx.h"
#include "dirtness_shader.h"
#include "glm/ext.hpp"

DirtnessShader::DirtnessShader() : Shader("DirtnessShader.frag", "TextureVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
    this->bindAttribLocation(1, "VertexColor" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->dirtmap_location = this->getUniformLocation("suciedad");
	this->dirtlevel_location = this->getUniformLocation("nivel_suciedad");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
}

void DirtnessShader::setTransformMatrix(const glm::mat4& m) {
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));
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
	static DirtnessShader _instance;
	return &_instance;
}
