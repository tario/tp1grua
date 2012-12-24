#ifndef __MATERIAL_COLOR_REFLEXION_H
#define __MATERIAL_TP3_H

#include "material.h"
#include "texture.h"
#include "shader.h"

class MaterialColorReflexion : public Material {
	public:
		MaterialColorReflexion(
			glm::vec3 color,
			Texture* reflection_map);
		void use(const glm::mat4& m);

		Shader::ConcreteSetter<float>
			*kaSetter,
			*kdSetter,
			*ksSetter,
			*glossinessSetter,
			*intensidadReflexionSetter;


	private:
		glm::vec3 color;
		Texture* reflection_map;
		Shader* shader;

		Shader::ConcreteSetter<glm::mat4>* transformMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* projectionMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* normalMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* cameraSetter;
		Shader::ConcreteSetter<glm::vec3>* colorSetter;

};

#endif