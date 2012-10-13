#include "stdafx.h"
#include "cabina.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "model_object.h"

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);
static const glm::vec3 gris_oscuro = glm::vec3(0.2, 0.2, 0.2);

Cabina::Cabina() : cubo(ocre), contra_peso(gris_oscuro) {
	m_contra_peso = glm::translate(glm::mat4(1.0), glm::vec3(-0.5,0.0,0.5));
	m_contra_peso = glm::scale(m_contra_peso, glm::vec3(0.4, 1.2, 0.4));
	m_brazo = ModelObject::line(glm::vec3(0.5, 0.0, 0.0), glm::vec3(4.0, 0.0, 0.0),  0.4f, 0.4f);
	angulo_brazo = 0.0;
}

void Cabina::dibujar(const glm::mat4& m) {
	this->cubo.dibujar(m);
	this->contra_peso.dibujar(m * m_contra_peso);
	this->brazo.dibujar(m * m_brazo);
}
#define M_PI       3.14159265358979323846
void Cabina::girar_brazo(float angulo) {
	if ((angulo > 0 && this->angulo_brazo+angulo < 60.0) || (angulo < 0 && this->angulo_brazo-angulo > -60.0)) {
		this->angulo_brazo += angulo;
		glm::vec3 punto_final = glm::vec3(4.0*cos(this->angulo_brazo*M_PI/180), 0.0, 4.0*sin(this->angulo_brazo*M_PI/180));

		this->m_brazo = ModelObject::line(glm::vec3(0.5, 0.0, 0.0), punto_final, 0.4f, 0.4f);
	}
}

