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
static const float proporcion_cabina = 0.35;

Grua::Grua() : 
	mo_torre(&torre, cell_matrix(-0.42,0.42,-0.42,0.42,-0.5, 0.5 - proporcion_cabina)), 
	mo_cabina(&cabina, cell_matrix(-0.5,0.5,-0.5,0.5,0.5 - proporcion_cabina,0.5)),
	angulo_cabina(0.0),
	_suciedad(0.4) {

	cabina.suciedad(_suciedad);
	torre.suciedad(_suciedad);
}

void Grua::girar_cabina(float angulo) {
	this->angulo_cabina += angulo;
	if (this->angulo_cabina < 0.0) angulo_cabina += 360.0;
	if (this->angulo_cabina > 360.0) angulo_cabina -= 360.0;

	// actualizar la matriz de modelo de la cabina
	mo_cabina.set_model_matrix(glm::rotate(glm::mat4(1.0), this->angulo_cabina, glm::vec3(0.0,0.0,1.0)) * cell_matrix(-0.5,0.5,-0.5,0.5,0.5 - proporcion_cabina, 0.5));
}

void Grua::dibujar(const glm::mat4& m) {
	// dibujar la torre y la cabina
	this->mo_torre.dibujar(m);
	this->mo_cabina.dibujar(m);
}

void Grua::girar_brazo(float angulo) {
	this->cabina.girar_brazo(angulo);
}

void Grua::longitud_cable(float delta) {
	this->cabina.longitud_cable(delta);
}

void Grua::cambiar_suciedad(float delta_suciedad) {
	_suciedad += delta_suciedad;
	if (_suciedad>1.0) _suciedad = 1.0;
	if (_suciedad<0.0) _suciedad = 0.0;

	cabina.suciedad(_suciedad);
	torre.suciedad(_suciedad);
}