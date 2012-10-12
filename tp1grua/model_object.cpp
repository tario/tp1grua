#include "stdafx.h"
#include "model_object.h"

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
