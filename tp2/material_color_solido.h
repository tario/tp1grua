#ifndef __MATERIAL_COLOR_SOLIDO_H
#define __MATERIAL_COLOR_SOLIDO_H

#include "material.h"
#include "solid_color_shader.h"

class MaterialColorSolido : public Material {
	public:
		MaterialColorSolido(const glm::vec3& color);
		void use(const glm::mat4& m);

	private:
		SolidColorShader* solidColorShader;
		glm::vec3 color;
};

#endif
