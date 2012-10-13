#include "stdafx.h"
#include "piso.h"

float cara1[] = {0.0, 0.0, 10.0, 0.0, 10.0, 10.0, 0.0, 10.0};
static CuboTexturado::Cara caras[] = {
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1)
};

Piso::Piso() : 
	cubo(new Texture("ladrillos.bmp"),
		caras) {
}

void Piso::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}
