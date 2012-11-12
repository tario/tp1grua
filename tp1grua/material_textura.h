#ifndef __MATERIAL_TEXTURA_H
#define __MATERIAL_TEXTURA_H

#include "material.h"
#include "texture_shader.h"
#include "texture.h"

class MaterialTextura : public Material {
	public:
		MaterialTextura(Texture* texture);
		void use(const glm::mat4& m);

	private:
		TextureShader* textureShader;
		Texture* texture;
};

#endif
