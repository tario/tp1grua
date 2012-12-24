#include "stdafx.h"
#include "material_color_solido.h"
#include "shader_program.h"

static ShaderProgram* shaderProgram = 0;
static ShaderProgram* phongShaderProgram = 0;

MaterialColorSolido::MaterialColorSolido(const glm::vec3& color, bool phong) : color(color) {
	if (phong) {
		if (shaderProgram == 0) {
		shaderProgram = new ShaderProgram("BasicColorFShader.frag", "tp3shader.vert"); 
		shaderProgram->bindAttribLocation(0, "VertexPosition" );
		shaderProgram->bindAttribLocation(1, "VertexNormal" );
		shaderProgram->link();
		}

		shader = new Shader(shaderProgram);
	} else {
		if (phongShaderProgram == 0) {
		phongShaderProgram = new ShaderProgram("ColorShader.frag", "tp3shader.vert");
		phongShaderProgram->bindAttribLocation(0, "VertexPosition" );
		phongShaderProgram->bindAttribLocation(1, "VertexNormal" );
		phongShaderProgram->link();
		}

		shader = new Shader(phongShaderProgram);
	}

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
