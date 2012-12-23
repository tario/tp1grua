#include "stdafx.h"
#include "material_target_quad.h"
#include "shader_program.h"

static ShaderProgram* targetQuadShaderProgram = 0;

MaterialTargetQuad::MaterialTargetQuad(const glm::vec3& color) : color(color) {
	if (targetQuadShaderProgram  == 0) {
		targetQuadShaderProgram  = new ShaderProgram("ColorShader.frag", "TargetQuad.vert");
		targetQuadShaderProgram ->bindAttribLocation(0, "VertexPosition" );
		targetQuadShaderProgram ->bindAttribLocation(1, "VertexNormal" );
		targetQuadShaderProgram ->link();

		shader = new Shader(targetQuadShaderProgram );
	} 

	nMatrixSetter = shader->setter<glm::mat4>("NormalMatrix");
	prMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	trMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	colorSetter = shader->setter<glm::vec3>("Color");
	posCamaraSetter = shader->setter<glm::vec3>("camera_position");
}
 
void MaterialTargetQuad::use(const glm::mat4& m) {
	trMatrixSetter->set(m);
	prMatrixSetter->set(Shader::projectionMatrix);
	nMatrixSetter->set(shader->compute_normal_matrix(m));
	colorSetter->set(color);
	posCamaraSetter->set(Shader::cameraPosition);

	shader->use();
}
