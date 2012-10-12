#include "stdafx.h"
#include "cabina.h"

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);

Cabina::Cabina() : cubo(ocre) {

}

void Cabina::dibujar(const glm::mat4& m) {
	this->cubo.dibujar(m);
}
