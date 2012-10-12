#include "stdafx.h"
#include "grua.h"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "cubo_color.h"
#include "cabina.h"
#include "torre.h"

static glm::mat4 cell_matrix(
	float xdown, float xup, float ydown, float yup, float zdown, float zup
	) {

	glm::mat4 model = glm::translate(glm::vec3( (xup+xdown)/2 ,(yup+ydown)/2, (zup+zdown)/2));
	model = glm::scale(model, glm::vec3(xup - xdown, yup - ydown, zup - zdown));
	return model;
}

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);

Grua::Grua() : 
	torre(new Torre(), cell_matrix(-0.35,0.35,-0.35,0.35,-0.5, 0.2) ), 
	cabina(new Cabina(), cell_matrix(-0.5,0.5,-0.5,0.5,0.2, 0.5)),
	angulo_cabina(0.0) {
}

void Grua::girar_cabina(float angulo) {
	this->angulo_cabina += angulo;
	if (this->angulo_cabina < 0.0) angulo_cabina += 360.0;
	if (this->angulo_cabina > 360.0) angulo_cabina -= 360.0;

	// actualizar la matriz de modelo de la cabina
	cabina.set_model_matrix(glm::rotate(glm::mat4(1.0), this->angulo_cabina, glm::vec3(0.0,0.0,1.0)) * cell_matrix(-0.5,0.5,-0.5,0.5,0.2, 0.5));
}

void Grua::dibujar(const glm::mat4& m) {
	// dibujar la torre y la cabina
	this->torre.dibujar(m);
	this->cabina.dibujar(m);
}