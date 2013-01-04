#ifndef __MATERIAL_COLOR_SOLIDO_H
#define __MATERIAL_COLOR_SOLIDO_H

#include "material.h"
#include "shader.h"

class MaterialColorSolido : public Material {
	public:
		MaterialColorSolido(const glm::vec3& color, bool phong=true);
		MaterialColorSolido(const glm::vec3& color, const std::string& fragment_shader);
		void use(const glm::mat4& m);

	private:
		Shader* shader;
		glm::vec3 color;

		Shader::ConcreteSetter<glm::mat4>* nMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* prMatrixSetter;
		Shader::ConcreteSetter<glm::mat4>* trMatrixSetter;
		Shader::ConcreteSetter<glm::vec3>* posCamaraSetter;
		Shader::ConcreteSetter<glm::vec3>* dirCamaraSetter;
		Shader::ConcreteSetter<glm::vec3>* colorSetter;

};

#endif
