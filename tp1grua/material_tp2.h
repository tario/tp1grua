#ifndef __MATERIAL_TP2_H
#define __MATERIAL_TP2_H

#include "material.h"
#include "texture.h"
#include "shader.h"

class MaterialTP2 : public Material {
	public:
		MaterialTP2(
			Texture* diffuse_map, 
			Texture* bump_map,
			Texture* reflection_map);
		void use(const glm::mat4& m);
	private:
		Texture* diffuse_map;
		Texture* bump_map;
		Texture* reflection_map;
		Shader* shader;

		Shader::ConcreteSetter<glm::mat4>* transformMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* projectionMatrixSetter;
		Shader::ConcreteSetter<glm::mat3>* normalMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* cameraSetter;
};

#endif