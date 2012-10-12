#include "stdafx.h"
#include "piso.h"

static const glm::vec3 gris = glm::vec3(0.5,0.5,0.5);

Piso::Piso() : cubo(gris) {
}

void Piso::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}
