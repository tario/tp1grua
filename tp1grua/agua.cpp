#include "stdafx.h"
#include "agua.h"

static float cara1[] = {0.0, 0.0, 5.0, 0.0, 5.0, 5.0, 0.0, 5.0};
static CuboTexturado::Cara caras[] = {
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1)
};

Agua::Agua() : texture("agua.bmp"), cubo(&texture, caras, false), olas(&texture) {
}

void Agua::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
	olas.dibujar(m);
}
