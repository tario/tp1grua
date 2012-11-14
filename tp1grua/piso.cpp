#include "stdafx.h"
#include "piso.h"

static float cara1[] = {0.0, 0.0, 10.0, 0.0, 10.0, 10.0, 0.0, 10.0};
static CuboTexturado::Cara caras[] = {
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1)
};

Piso::Piso() :
	material(new Texture("piedras.bmp"), new Texture("normal-piedras.bmp"), 0.2, 0.3, 0.5),
	cubo(&material, caras) {
}

void Piso::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}
