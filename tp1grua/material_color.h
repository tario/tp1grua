#ifndef __MATERIAL_COLOR_H
#define __MATERIAL_COLOR_H

#include "material.h"
#include "color_shader.h"

class MaterialColor : public Material {
	public:
		MaterialColor();
		void use(const glm::mat4& m);

	private:
		ColorShader* colorShader;
};

#endif
