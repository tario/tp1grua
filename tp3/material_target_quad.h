#ifndef __MATERIAL_TARGET_QUAD_H
#define __MATERIAL_TARGET_QUAD_H

#include "material.h"
#include "shader.h"

class MaterialTargetQuad : public Material {
	public:
		MaterialTargetQuad(const glm::vec3& color, bool border_truncate = true);
		void use(const glm::mat4& m);

	private:
		Shader* shader;
		glm::vec3 color;

		Shader::ConcreteSetter<glm::mat4>* nMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* prMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* trMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* posCamaraSetter;
		Shader::ConcreteSetter<glm::vec3>* colorSetter;

};

#endif
