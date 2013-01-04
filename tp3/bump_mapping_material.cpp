#include "stdafx.h"
#include "bump_mapping_material.h"
#include "texture.h"

MaterialBumpMapping::MaterialBumpMapping(Texture* texture, Texture* bumpMap, float ka, float kd, float ks) :
	ka(ka), kd(kd), ks(ks),
	texture(texture),
	bumpMap(bumpMap) {
	shader = BumpMappingShader::instance();
}

void MaterialBumpMapping::use(const glm::mat4& m) {
	shader->use();

	texture->load(0);
	bumpMap->load(1);
	shader->setTextureUnit(0);
	shader->setNormalmapUnit(1);
	shader->setLightningParameters(ka, kd, ks);
	shader->setTransformMatrix(m);
	shader->setProjectionMatrix(Shader::projectionMatrix);
	shader->setCameraDirection(Shader::cameraDirection);
}
