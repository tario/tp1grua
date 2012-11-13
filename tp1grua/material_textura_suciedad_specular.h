#ifndef __MATERIAL_TEXTURA_SUCIEDAD_SPECULAR_H
#define __MATERIAL_TEXTURA_SUCIEDAD_SPECULAR_H

#include "material.h"
#include "texture.h"
#include "specular_dirtness_shader.h"

class MaterialTexturaSuciedadSpecular : public Material {
	public:
		MaterialTexturaSuciedadSpecular(
			Texture* texture, 
			Texture* dirtTexture,
			Texture* specularMap,
			float _suciedad);
		void use(const glm::mat4& m);

		void cambiar_suciedad(float suciedad);
	private:
		Texture* texture;
		Texture* dirtTexture;
		Texture* specularMap;
		SpecularDirtnessShader* specularDirtnessShader;

		float suciedad;
};

#endif