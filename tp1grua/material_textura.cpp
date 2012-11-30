#include "stdafx.h"
#include "material_textura.h"
#include "texture.h"

MaterialTextura::MaterialTextura(Texture* texture) :
	texture(texture) {
	shader = new Shader("TextureFShader.frag", "TextureVShader.vert");

	shader->bindAttribLocation(0, "VertexPosition" );
	shader->bindAttribLocation(1, "VertexNormal" );
	shader->bindAttribLocation(2, "VertexTexCoord" );
	shader->link();

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
