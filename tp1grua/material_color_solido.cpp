#include "stdafx.h"
#include "material_color_solido.h"

MaterialColorSolido::MaterialColorSolido(const glm::vec3& color) : color(color) {
	solidColorShader = SolidColorShader::instance();
}

void MaterialColorSolido::use(const glm::mat4& m) {
	solidColorShader->use();

	solidColorShader->setTransformMatrix(m);
	solidColorShader->setProjectionMatrix(Shader::projectionMatrix);
	solidColorShader->setCameraDirection(Shader::cameraDirection);
	solidColorShader->setColor(color);
}
