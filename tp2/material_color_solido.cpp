#include "stdafx.h"
#include "material_color_solido.h"

MaterialColorSolido::MaterialColorSolido(const glm::vec3& color, bool phong) : color(color) {
	if (phong) {
		shader = new Shader("BasicColorFShader.frag", "BasicColorVShader.vert"); 
	} else {
		shader = new Shader("ColorShader.frag", "BasicColorVShader.vert"); 
	}
	shader->bindAttribLocation(0, "VertexPosition" );
	shader->bindAttribLocation(1, "VertexNormal" );
	shader->link();

	nMatrixSetter = shader->setter<glm::mat4>("NormalMatrix");
	prMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	trMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	colorSetter = shader->setter<glm::vec3>("Color");
	posCamaraSetter = shader->setter<glm::vec3>("camera_position");
}
 
void MaterialColorSolido::use(const glm::mat4& m) {
	trMatrixSetter->set(m);
	prMatrixSetter->set(Shader::projectionMatrix);
	nMatrixSetter->set(shader->compute_normal_matrix(m));
	colorSetter->set(color);
	posCamaraSetter->set(Shader::cameraPosition);

	shader->use();
}
