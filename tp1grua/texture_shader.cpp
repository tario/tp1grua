#include "stdafx.h"
#include "texture_shader.h"
#include "glm/ext.hpp"

TextureShader::TextureShader() : Shader("TextureFShader.frag", "TextureVShader.vert") { 
	this->bindAttribLocation(0, "VertexPosition" );
    this->bindAttribLocation(1, "VertexColor" );
	this->link();

	this->texture_location = this->getUniformLocation("texture1");
	this->transform_matrix_index = this->getUniformLocation("TransformMatrix");
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
