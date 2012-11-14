#ifndef __MATERIAL_BUMP_MAPPING_H
#define __MATERIAL_BUMP_MAPPING_H

#include "material.h"
#include "bump_mapping_shader.h"
#include "texture.h"

class MaterialBumpMapping : public Material {
	public:
		MaterialBumpMapping(Texture* texture, Texture* bumpMap,
			float ka=1.0, float kd=0.0, float ks=0.0
			);
		void use(const glm::mat4& m);

	private:
		BumpMappingShader* shader;
		Texture* texture;
		Texture* bumpMap;

		float ka, kd, ks;
};

#endif
