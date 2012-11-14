#include "stdafx.h"
#include "material_color.h"

MaterialColor::MaterialColor() {
	colorShader = ColorShader::instance();
}

void MaterialColor::use(const glm::mat4& m) {
	colorShader->use();

	colorShader->setTransformMatrix(m);
	colorShader->setProjectionMatrix(Shader::projectionMatrix);
	colorShader->setCameraDirection(Shader::cameraDirection);
}
