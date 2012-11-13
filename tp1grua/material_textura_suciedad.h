#ifndef __MATERIAL_TEXTURA_SUCIEDAD_H
#define __MATERIAL_TEXTURA_SUCIEDAD_H

#include "material.h"
#include "texture.h"
#include "dirtness_shader.h"

class MaterialTexturaSuciedad : public Material {
	public:
		MaterialTexturaSuciedad(Texture* texture, Texture* dirtTexture, float _suciedad);
		void use(const glm::mat4& m);

		void cambiar_suciedad(float suciedad);
	private:
		Texture* texture;
		Texture* dirtTexture;
		DirtnessShader* dirtnessShader;

		float suciedad;
};

#endif