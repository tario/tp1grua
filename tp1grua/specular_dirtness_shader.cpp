#include "stdafx.h"
#include "specular_dirtness_shader.h"

SpecularDirtnessShader::SpecularDirtnessShader() : 
	DirtnessShader("SpecularDirtnessShader.frag", "TextureVShader.vert") {

	this->specularmap_location = this->getUniformLocation("specularmap");
}

void SpecularDirtnessShader::setSpecularmapUnit(int unitnumber) {
	glUniform1i(this->specularmap_location, unitnumber);
}

SpecularDirtnessShader* SpecularDirtnessShader::instance() {
	static SpecularDirtnessShader _instance;
	return &_instance;
}
