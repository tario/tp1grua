#include "stdafx.h"
#include "material_textura.h"
#include "texture.h"

MaterialTextura::MaterialTextura(Texture* texture, float ka, float kd, float ks) :
	ka(ka), kd(kd), ks(ks),
	texture(texture) {
	textureShader = TextureShader::instance();
}

void MaterialTextura::use(const glm::mat4& m) {
	textureShader->use();

	texture->load(0);
	textureShader->setTextureUnit(0);
	textureShader->setLightningParameters(ka, kd, ks);
	textureShader->setTransformMatrix(m);
	textureShader->setProjectionMatrix(Shader::projectionMatrix);
	textureShader->setCameraDirection(Shader::cameraDirection);
}
