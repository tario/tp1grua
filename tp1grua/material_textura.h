#ifndef __MATERIAL_TEXTURA_H
#define __MATERIAL_TEXTURA_H

#include "material.h"
#include "texture_shader.h"
#include "texture.h"

class MaterialTextura : public Material {
	public:
		MaterialTextura(Texture* texture,
			float ka=1.0, float kd=0.0, float ks=0.0
			);
		void use(const glm::mat4& m);

	private:
		TextureShader* textureShader;
		Texture* texture;

		float ka, kd, ks;
};

#endif
