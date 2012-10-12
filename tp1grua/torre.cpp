#include "stdafx.h"
#include "torre.h"

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);

Torre::Torre() : cubo(ocre) {

}

void Torre::dibujar(const glm::mat4& m) {
	this->cubo.dibujar(m);
}
