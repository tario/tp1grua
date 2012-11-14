#ifndef __MATERIAL_COLOR_SOLIDO_H
#define __MATERIAL_COLOR_SOLIDO_H

#include "material.h"
#include "color_shader.h"

class MaterialColorSolido : public Material {
	public:
		MaterialColorSolido();
		void use(const glm::mat4& m);

	private:
		ColorShader* colorShader;
};

#endif
