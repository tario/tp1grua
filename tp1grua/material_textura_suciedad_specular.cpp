#include "stdafx.h"
#include "material_textura_suciedad_specular.h"

MaterialTexturaSuciedadSpecular::MaterialTexturaSuciedadSpecular(
	Texture* texture, 
	Texture* dirtTexture,
	Texture* specularMap,
	float _suciedad) :
	texture(texture),
	dirtTexture(dirtTexture),
	specularMap(specularMap),
	suciedad(_suciedad) { 

	this->specularDirtnessShader = SpecularDirtnessShader::instance();
}

void MaterialTexturaSuciedadSpecular::cambiar_suciedad(float _suciedad) {
	this->suciedad = _suciedad;
}

void MaterialTexturaSuciedadSpecular::use(const glm::mat4& m) {
	this->specularDirtnessShader->use();

	texture->load(0);
	dirtTexture->load(1);
	specularMap->load(2);

	specularDirtnessShader->setTextureUnit(0);
	specularDirtnessShader->setDirtmapUnit(1);
	specularDirtnessShader->setSpecularmapUnit(2);
	specularDirtnessShader->setDirtlevel(this->suciedad);
	specularDirtnessShader->setTransformMatrix(m);
	specularDirtnessShader->setProjectionMatrix(Shader::projectionMatrix);
	specularDirtnessShader->setCameraDirection(Shader::cameraDirection);
}
