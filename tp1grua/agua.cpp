#include "stdafx.h"
#include "agua.h"

static const glm::vec3 azul= glm::vec3(0.0,0.0,0.8);

Agua::Agua() : cubo(azul) {
}

void Agua::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}
