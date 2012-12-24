#ifndef __MATERIAL_DIFUSO_RELIEVE_H
#define __MATERIAL_DIFUSO_RELIEVE_H

#include "material.h"
#include "texture.h"
#include "shader.h"

class MaterialDifusoRelieve : public Material {
	public:
		MaterialDifusoRelieve(
			Texture* diffuse_map, 
			Texture* normal_map);
		void use(const glm::mat4& m);

		Shader::ConcreteSetter<float>
			*kaSetter,
			*kdSetter,
			*ksSetter,
			*glossinessSetter,
			*intensidadDifusoSetter,
			*intensidadRelieveSetter;


	private:
		Texture* diffuse_map;
		Texture* bump_map;
		Shader* shader;

		Shader::ConcreteSetter<glm::mat4>* transformMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* projectionMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* normalMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* cameraSetter;
};

#endif