#include "stdafx.h"
#include "material_color_reflexion.h"

static ShaderProgram* shaderProgram = 0;

MaterialColorReflexion::MaterialColorReflexion(
	glm::vec3 color, 
	Texture* reflection_map) :
	color(color),
	reflection_map(reflection_map) { 

	if (shaderProgram == 0) {
		shaderProgram = new ShaderProgram("color_con_reflexion.frag", "tp3Shader.vert");
		shaderProgram->bindAttribLocation(0, "VertexPosition" );
		shaderProgram->bindAttribLocation(1, "VertexNormal" );
		shaderProgram->bindAttribLocation(2, "VertexTexCoord" );
		shaderProgram->bindAttribLocation(3, "VertexNormalX" );
		shaderProgram->link();
	}

	this->shader = new Shader(shaderProgram);

	this->shader->setter<int>("diffuse_map")->set(0);
	this->shader->setter<int>("bump_map")->set(1);
	this->shader->setter<int>("reflection_map")->set(2);
	kaSetter = shader->setter<float>("ka")->set(0.6);
	kdSetter = shader->setter<float>("kd")->set(0.3);
	ksSetter = shader->setter<float>("ks")->set(0.4);
	glossinessSetter = shader->setter<float>("glossiness")->set(4.0);
	intensidadReflexionSetter = shader->setter<float>("intensidad_reflexion")->set(0.0);

	transformMatrixSetter = shader->setter<glm::mat4>("TransformMatrix");
	normalMatrixSetter = shader->setter<glm::mat4>("NormalMatrix");
	projectionMatrixSetter = shader->setter<glm::mat4>("ProjectionMatrix");
	cameraSetter = shader->setter<glm::vec3>("camera_position");
	colorSetter = shader->setter<glm::vec3>("Color");
}

void MaterialColorReflexion::use(const glm::mat4& m) {
	transformMatrixSetter->set(m);
	normalMatrixSetter->set(shader->compute_normal_matrix(m));
	projectionMatrixSetter->set(Shader::projectionMatrix);
	cameraSetter->set(Shader::cameraPosition);
	colorSetter->set(color);

	this->shader->use();

	reflection_map->load(2);
}
