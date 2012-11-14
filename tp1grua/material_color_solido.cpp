#include "stdafx.h"
#include "material_color_solido.h"

MaterialColorSolido::MaterialColorSolido() {
	colorShader = ColorShader::instance();
}

void MaterialColorSolido::use(const glm::mat4& m) {
	colorShader->use();

	colorShader->setTransformMatrix(m);
	colorShader->setProjectionMatrix(Shader::projectionMatrix);
	colorShader->setCameraDirection(Shader::cameraDirection);
}
