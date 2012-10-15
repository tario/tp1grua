#include "stdafx.h"
#include "cabina.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "model_object.h"

static const glm::vec3 gris_oscuro = glm::vec3(0.4, 0.4, 0.4);
static const glm::vec3 negro = glm::vec3(0.0,0.0,0.0);

static CuboTexturado::Cara coordenadas_textura[] = {
	CuboTexturado::Cara(0.5087,0.287, 0.1,0.287, 0.1,0.5839, 0.5087,0.5839),
	CuboTexturado::Cara(0.0,1.0, 0.0,0.5839, 0.5556,0.5839, 0.5556,1.0),
	CuboTexturado::Cara(0.5556,1.0, 0.5556,0.5839, 1.0,0.5839, 1.0,1.0),
	CuboTexturado::Cara(0.5556,1.0 ,0.5556,0.5839, 0.0,0.5839, 0.0,1.0),
	CuboTexturado::Cara(0.3,0.287, 0.7,0.287, 0.7,0.5839, 0.3,0.5839),
	CuboTexturado::Cara(0.0,0.1,0.0,0.0,0.1,0.0,0.1,0.1)

};

Cabina::Cabina() :
	textura_cabina("textura.bmp"),
	cubo(&textura_cabina, coordenadas_textura), 
	contra_peso(gris_oscuro), cable(negro), gancho(negro),
	mo_cubo(&cubo, ModelObject::cell_matrix(-0.83,0.83,-0.5,0.5,-0.5,0.5)),
	mo_contra_peso(&contra_peso, glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(-0.83, 0.0,0.5)), glm::vec3(0.4, 1.2, 0.4))),
	mo_cable(&cable),
	mo_gancho(&gancho),
	mo_brazo(&brazo) {
	angulo_brazo = 0.0;
	_longitud_cable = 4.0;
	actualizar_matrices_brazo();
}

void Cabina::dibujar(const glm::mat4& m) {
	this->mo_cubo.dibujar(m);
	this->mo_contra_peso.dibujar(m);
	this->mo_brazo.dibujar(m);
	this->mo_cable.dibujar(m);
	this->mo_gancho.dibujar(m);
}
#define M_PI       3.14159265358979323846
void Cabina::girar_brazo(float angulo) {
	if ((angulo > 0 && this->angulo_brazo+angulo < 75.0) || (angulo < 0 && this->angulo_brazo-angulo > -75.0)) {
		this->angulo_brazo += angulo;

		actualizar_matrices_brazo();
	}
}

void Cabina::actualizar_matrices_brazo() {
	glm::vec3 punto_final = glm::vec3(4.0*cos(this->angulo_brazo*M_PI/180), 0.0, 4.0*sin(this->angulo_brazo*M_PI/180));

	// = ModelObject::line(glm::vec3(0.5, 0.0, 0.0), punto_final, 0.4f, 0.4f);
	this->mo_brazo.set_model_matrix(ModelObject::line(glm::vec3(0.5, 0.0, 0.0), punto_final, 0.8f, 0.8f));
	//this->m_cable = ModelObject::line(punto_final + glm::vec3(0.0,0.0,-5.0), punto_final, 0.1f, 0.1f);
	this->mo_cable.set_model_matrix(ModelObject::cell_matrix(
		punto_final[0] - 0.02,
		punto_final[0] + 0.02,
		punto_final[1] - 0.02,
		punto_final[1] + 0.02,
		punto_final[2] - _longitud_cable,
		punto_final[2])
		);

	this->mo_gancho.set_model_matrix(ModelObject::cell_matrix(
		punto_final[0] - 0.1,
		punto_final[0] + 0.1,
		punto_final[1] - 0.1,
		punto_final[1] + 0.1,
		punto_final[2] - _longitud_cable - 0.1,
		punto_final[2] - _longitud_cable));
}

void Cabina::longitud_cable(float delta) {
	if (delta < 0 && _longitud_cable < 0.2) return;
	if (delta > 0 && _longitud_cable > 30.0) return;

	_longitud_cable = _longitud_cable + delta;
	actualizar_matrices_brazo();
}
