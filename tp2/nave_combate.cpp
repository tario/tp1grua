#include "stdafx.h"
#include "nave_combate.h"

static float cara2[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
static CuboTexturado::Cara caras2[] = {
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2)
};

NaveCombate::NaveCombate() : 
	material_cubo(glm::vec3(0.4,0.4,0.4)),
	cubo(&material_cubo, caras2, false) {

}

void NaveCombate::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}