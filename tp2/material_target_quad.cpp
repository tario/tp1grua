#include "stdafx.h"
#include "material_target_quad.h"
#include "shader_program.h"

static ShaderProgram* targetQuadShaderProgram = 0;
static ShaderProgram* bezierCurveShaderProgram = 0;

MaterialTargetQuad::MaterialTargetQuad(const glm::vec3& color, bool border_truncate) : color(color) {
	if (border_truncate) {
		if (targetQuadShaderProgram  == 0) {
			targetQuadShaderProgram  = new ShaderProgram("ColorShader.frag", "TargetQuad.vert");
			targetQuadShaderProgram ->bindAttribLocation(0, "VertexPosition" );
			targetQuadShaderProgram ->bindAttribLocation(1, "VertexNormal" );
			targetQuadShaderProgram ->link();
		}

		shader = new Shader(targetQuadShaderProgram );
	} else {
		if (bezierCurveShaderProgram  == 0) {
			bezierCurveShaderProgram  = new ShaderProgram("ColorShader.frag", "BezierCurve.vert");
			bezierCurveShaderProgram ->bindAttribLocation(0, "VertexPosition" );
			bezierCurveShaderProgram ->bindAttribLocation(1, "VertexNormal" );
			bezierCurveShaderProgram ->link();
		}

		shader = new Shader(bezierCurveShaderProgram );
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
