#include "stdafx.h"
#include "material_textura_suciedad.h"

MaterialTexturaSuciedad::MaterialTexturaSuciedad(Texture* texture, Texture* dirtTexture, float _suciedad) :
	texture(texture),
	dirtTexture(dirtTexture),
	suciedad(_suciedad) { 

	this->dirtnessShader = DirtnessShader::instance();
}

void MaterialTexturaSuciedad::cambiar_suciedad(float _suciedad) {
	this->suciedad = _suciedad;
}

void MaterialTexturaSuciedad::use(const glm::mat4& m) {
	this->dirtnessShader->use();

	texture->load(0);
	dirtTexture->load(1);

	dirtnessShader->setTextureUnit(0);
	dirtnessShader->setDirtmapUnit(1);
	dirtnessShader->setDirtlevel(this->suciedad);
	dirtnessShader->setTransformMatrix(m);
	dirtnessShader->setProjectionMatrix(Shader::projectionMatrix);
	dirtnessShader->setCameraDirection(Shader::cameraDirection);
}
