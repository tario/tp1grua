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

NaveCombate::NaveCombate(Texture* mapa_reflexion_universo) : 
	mapa_difuso_nave("nave.bmp"),
	material_cubo(&mapa_difuso_nave, NullTexture::instance(), mapa_reflexion_universo),
	cubo(&material_cubo, caras2) {

		material_cubo.intensidadDifusoSetter->set(0.7);
		material_cubo.intensidadReflexionSetter->set(0.3);
		material_cubo.intensidadGrisSetter->set(0.0);
		material_cubo.intensidadRelieveSetter->set(0.0);
		material_cubo.kaSetter->set(0.1);
}

void NaveCombate::dibujar(const glm::mat4& m) {
	cubo.dibujar(m);
}