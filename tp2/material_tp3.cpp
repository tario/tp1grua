#include "stdafx.h"
#include "material_tp3.h"


MaterialTP3::MaterialTP3(
	Texture* diffuse_map, 
	Texture* bump_map,
	Texture* reflection_map) :
	diffuse_map(diffuse_map),
	bump_map(bump_map),
	reflection_map(reflection_map) { 

	this->shader = new Shader("tp3Shader.frag", "tp3Shader.vert");

	shader->bindAttribLocation(0, "VertexPosition" );
	shader->bindAttribLocation(1, "VertexNormal" );
	shader->bindAttribLocation(2, "VertexTexCoord" );
	shader->bindAttribLocation(3, "VertexNormalX" );
	shader->link();

	this->shader->setter<int>("diffuse_map")->set(0);
	this->shader->setter<int>("bump_map")->set(1);
	this->shader->setter<int>("reflection_map")->set(2);
	kaSetter = shader->setter<float>("ka")->set(0.6);
	kdSetter = shader->setter<float>("kd")->set(0.3);
	ksSetter = shader->setter<float>("ks")->set(0.4);
	glossinessSetter = shader->setter<float>("glossiness")->set(4.0);
	intensidadGrisSetter = shader->setter<float>("intensidad_gris")->set(0.4);
	intensidadDifusoSetter = shader->setter<float>("intensidad_difuso")->set(0.0);
	intensidadRelieveSetter = shader->setter<float>("intensidad_relieve")->set(0.0);
	intensidadReflexionSetter = shader->setter<float>("intensidad_reflexion")->set(0.0);

	transformMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	normalMatrixSetter = shader->setter<glm::mat4>("NormalMatrix");
	projectionMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	cameraSetter = shader->setter<glm::vec3>("camera_position");
}

void MaterialTP3::use(const glm::mat4& m) {
	transformMatrixSetter->set(m);
	normalMatrixSetter->set(shader->compute_normal_matrix(m));
	projectionMatrixSetter->set(Shader::projectionMatrix);
	cameraSetter->set(Shader::cameraPosition);

	this->shader->use();

	diffuse_map->load(0);
	bump_map->load(1);
	reflection_map->load(2);
}
