#include "stdafx.h"
#include "model_object.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

ModelObject::ModelObject(Dibujable* primitiva) : primitiva(primitiva), model_matrix(glm::mat4(1.0)) {
}

ModelObject::ModelObject(Dibujable* primitiva, const glm::mat4& model_matrix) : primitiva(primitiva), model_matrix(model_matrix) {
}

void ModelObject::dibujar(const glm::mat4& project_view) {
	this->primitiva->dibujar(project_view * model_matrix);
}

void ModelObject::set_model_matrix(const glm::mat4& m) {
	this->model_matrix = m;
}

glm::mat4 ModelObject::cell_matrix(float xdown, float xup, float ydown, float yup, float zdown, float zup) {
	glm::mat4 model = glm::translate(glm::vec3( (xup+xdown)/2 ,(yup+ydown)/2, (zup+zdown)/2));
	model = glm::scale(model, glm::vec3(xup - xdown, yup - ydown, zup - zdown));
	return model;
}

glm::mat4 ModelObject::line(const glm::vec3& p0, const glm::vec3& p1, float anchox, float anchoy) {
	float distance = glm::distance(p0,p1);
	glm::vec3 p2(p0[0], p0[1], p0[2]+distance);
	glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(p0[0], p0[1], p0[2]));
	glm::vec3 v1 = p2-p0;
	glm::vec3 v2 = p1-p0;
	float angle = glm::angle(glm::normalize(v1), glm::normalize(v2));
	glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
	m = glm::rotate(m, angle, normal);
	m = glm::translate(m, glm::vec3(0,0,distance/2));
	m = glm::scale(m, glm::vec3(anchox, anchoy,distance));

	return m;
}
