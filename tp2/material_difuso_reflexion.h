#ifndef __MATERIAL_DIFUSO_REFLEXION_H
#define __MATERIAL_DIFUSO_REFLEXION_H

#include "material.h"
#include "texture.h"
#include "shader.h"

class MaterialDifusoReflexion : public Material {
	public:
		MaterialDifusoReflexion(
			Texture* diffuse_map, 
			Texture* reflection_map);
		void use(const glm::mat4& m);

		Shader::ConcreteSetter<float>
			*kaSetter,
			*kdSetter,
			*ksSetter,
			*glossinessSetter,
			*intensidadDifusoSetter,
			*intensidadReflexionSetter;


	private:
		Texture* diffuse_map;
		Texture* reflection_map;
		Shader* shader;

		Shader::ConcreteSetter<glm::mat4>* transformMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* projectionMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* normalMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* cameraSetter;

};

#endif