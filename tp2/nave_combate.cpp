#include "stdafx.h"
#include "nave_combate.h"
#include "segmento_recta.h"

static float cara2[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
static CuboTexturado::Cara caras2[] = {
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2)
};

class ConjuntoPuntos : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		ret.push_back(Punto(-0.5,-0.5));
		ret.push_back(Punto(-0.5,0.5));
		ret.push_back(Punto(0.5,0.5));
		ret.push_back(Punto(0.5,-0.5));
		return ret;
	};
};

NaveCombate::NaveCombate(Texture* mapa_reflexion_universo) : 
	mapa_difuso_nave("nave.bmp"),
	material_cubo(&mapa_difuso_nave, NullTexture::instance(), mapa_reflexion_universo),
	cubo(&material_cubo, caras2) {

		material_cubo.ksSetter->set(0.0);
		material_cubo.kdSetter->set(1.0);
		material_cubo.intensidadDifusoSetter->set(0.7);
		material_cubo.intensidadReflexionSetter->set(0.3);
		material_cubo.intensidadGrisSetter->set(0.0);
		material_cubo.intensidadRelieveSetter->set(0.0);
		material_cubo.kaSetter->set(0.0);

	SegmentoRecta curva(glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,0.0,2.0));
	ConjuntoPuntos funcionConjuntoPuntos;
	superficie_barrido = new Barrido(&funcionConjuntoPuntos, &curva, 0, 1.0, &material_cubo);
}

void NaveCombate::dibujar(const glm::mat4& m) {
	superficie_barrido->dibujar(m);
	//cubo.dibujar(m);
}