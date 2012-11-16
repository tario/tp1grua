#include "stdafx.h"
#include "material_tp2.h"


MaterialTP2::MaterialTP2(
	Texture* diffuse_map, 
	Texture* bump_map,
	Texture* reflection_map) :
	diffuse_map(diffuse_map),
	bump_map(bump_map),
	reflection_map(reflection_map) { 

	this->shader = new Shader("tp2Shader.frag", "tp2Shader.vert");

	shader->bindAttribLocation(0, "VertexPosition" );
	shader->bindAttribLocation(1, "VertexNormal" );
	shader->bindAttribLocation(2, "VertexTexCoord" );
	shader->link();

	this->shader->setter<int>("diffuse_map")->set(0);
	this->shader->setter<int>("bump_map")->set(1);
	this->shader->setter<int>("reflection_map")->set(2);
	shader->setter<float>("ka")->set(0.2);
	shader->setter<float>("kd")->set(0.4);
	shader->setter<float>("ks")->set(0.4);
	shader->setter<float>("glossiness")->set(4.0);
	shader->setter<float>("intensidad_gris")->set(0.0);
	shader->setter<float>("intensidad_difuso")->set(1.0);

	transformMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	normalMatrixSetter = shader->setter<glm::mat3>("NormalMatrix");
	projectionMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	cameraSetter = shader->setter<glm::vec3>("camera_direction");
}

void MaterialTP2::use(const glm::mat4& m) {
	transformMatrixSetter->set(m);
	normalMatrixSetter->set(shader->compute_normal_matrix(m));
	projectionMatrixSetter->set(Shader::projectionMatrix);
	cameraSetter->set(Shader::cameraDirection);

	this->shader->use();

	diffuse_map->load(0);
	bump_map->load(1);
	reflection_map->load(2);
}
