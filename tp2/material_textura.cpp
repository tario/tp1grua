#include "stdafx.h"
#include "material_textura.h"
#include "texture.h"
#include "shader_program.h"

static ShaderProgram* textureShaderProgram = 0;

MaterialTextura::MaterialTextura(Texture* texture) :
	texture(texture) {

	if (textureShaderProgram == 0) {
		textureShaderProgram = new ShaderProgram("TextureFShader.frag", "tp3shader.vert");

		textureShaderProgram->bindAttribLocation(0, "VertexPosition" );
		textureShaderProgram->bindAttribLocation(1, "VertexNormal" );
		textureShaderProgram->bindAttribLocation(2, "VertexTexCoord" );
		textureShaderProgram->link();
	}

	shader = new Shader(textureShaderProgram);

	shader->setter<int>("texture1")->set(0);
	transformMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	normalMatrixSetter = shader->setter<glm::mat4>("NormalMatrix");
	projectionMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	cameraSetter = shader->setter<glm::vec3>("camera_direction");
}

void MaterialTextura::use(const glm::mat4& m) {
	transformMatrixSetter->set(m);
	normalMatrixSetter->set(shader->compute_normal_matrix(m));
	projectionMatrixSetter->set(Shader::projectionMatrix);
	cameraSetter->set(Shader::cameraDirection);
	shader->use();

	texture->load(0);
}
