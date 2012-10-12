#include "stdafx.h" 
#include "brazo.h"

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);

Brazo::Brazo() : cubo(ocre) {
}

void Brazo::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}
