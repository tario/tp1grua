#ifndef __MATERIAL_TP3_H
#define __MATERIAL_TP3_H

#include "material.h"
#include "texture.h"
#include "shader.h"

class MaterialTP3 : public Material {
	public:
		MaterialTP3(
			Texture* diffuse_map, 
			Texture* bump_map,
			Texture* reflection_map);
		void use(const glm::mat4& m);

		Shader::ConcreteSetter<float>
			*kaSetter,
			*kdSetter,
			*ksSetter,
			*glossinessSetter,
			*intensidadGrisSetter,
			*intensidadDifusoSetter,
			*intensidadRelieveSetter,
			*intensidadReflexionSetter;


	private:
		Texture* diffuse_map;
		Texture* bump_map;
		Texture* reflection_map;
		Shader* shader;

		Shader::ConcreteSetter<glm::mat4>* transformMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* projectionMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* normalMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* cameraSetter;

};

#endif