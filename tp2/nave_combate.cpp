#include "stdafx.h"
#include "nave_combate.h"
#include "segmento_recta.h"
#include "curva_constante.h" 

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

class ConjuntoPuntosAlas : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		if (t<0.1) {
		ret.push_back(Punto(0.0,-0.1));
		ret.push_back(Punto(5.0*(t+0.1),-0.05));
		ret.push_back(Punto(0.0,0.0));
		ret.push_back(Punto(-5.0*(t+0.1),-0.05));
		} else {
		ret.push_back(Punto(0.0,-0.1));
		ret.push_back(Punto(1.0-(t-0.1)*0.2,-0.05));
		ret.push_back(Punto(0.0,0.0));
		ret.push_back(Punto(-1.0+(t-0.1)*0.2,-0.05));
		}
		return ret;
	};
};


class ConjuntoPuntosBase : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		if (t<0.4) {
		ret.push_back(Punto(-0.4,-0.1));
		ret.push_back(Punto(-0.25,0.1));
		ret.push_back(Punto(0.25,0.1));
		ret.push_back(Punto(0.4,-0.1));
		} else {
		ret.push_back(Punto(-0.4+(t-0.4)*0.4,-0.1+(t-0.4)*0.1/0.6));
		ret.push_back(Punto(-0.25+(t-0.4)*0.09/0.6,0.1-(t-0.4)*0.1/0.6));
		ret.push_back(Punto(0.25-(t-0.4)*0.09/0.6,0.1-(t-0.4)*0.1/0.6));
		ret.push_back(Punto(0.4-(t-0.4)*0.4,-0.1+(t-0.4)*0.1/0.6));
		}
		return ret;
	};
};
class ConjuntoPuntosCabina : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		ret.push_back(Punto(-0.4,-0.1));
		ret.push_back(Punto(-0.25,-0.2-t*0.1));
		ret.push_back(Punto(0.25,-0.2-t*0.1));
		ret.push_back(Punto(0.4,-0.1));
		return ret;
	};
};
class ConjuntoPuntosTecho : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		if (t<0.8) {
		ret.push_back(Punto(-0.25,-0.2-t*0.09/0.6));
		ret.push_back(Punto(-0.22,-0.225-t*0.09/0.6));
		ret.push_back(Punto(0.22,-0.225-t*0.09/0.6));
		ret.push_back(Punto(0.25,-0.2-t*0.09/0.6));
		} else {
		ret.push_back(Punto(-0.25,-0.3+(t-0.8)*0.2));
		ret.push_back(Punto(-0.22,-0.325+(t-0.8)*0.325));
		ret.push_back(Punto(0.22,-0.325+(t-0.8)*0.325));
		ret.push_back(Punto(0.25,-0.3+(t-0.8)*0.2));
		}
		return ret;
	};
};
class ConjuntoPuntosVidrio : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		ret.push_back(Punto(-0.4+t*0.4/5,-0.1+t/30.0));
		ret.push_back(Punto(-0.25,-0.3+t*0.04));
		ret.push_back(Punto(0.25,-0.3+t*0.04));
		ret.push_back(Punto(0.4-t*0.4/5,-0.1+t/30.0));
		return ret;
	};
};


NaveCombate::NaveCombate(Texture* mapa_reflexion_universo) : 
	mapa_difuso_nave("nave.bmp"),
	material_cubo(&mapa_difuso_nave, NullTexture::instance(), mapa_reflexion_universo),
	cubo(&material_cubo, caras2),
	material_color(glm::vec3(0.0,0.0,0.0)) {

		material_cubo.ksSetter->set(0.2);
		material_cubo.kdSetter->set(1.0);
		material_cubo.intensidadDifusoSetter->set(0.6);
		material_cubo.intensidadReflexionSetter->set(0.4);
		material_cubo.intensidadGrisSetter->set(0.0);
		material_cubo.intensidadRelieveSetter->set(0.0);
		material_cubo.kaSetter->set(0.1);
		material_cubo.glossinessSetter->set(9.0);


	SegmentoRecta curva_alas(glm::vec3(0.5,0.0,0.0), glm::vec3(0.0,0.0,0.0));
	CurvaConstante derivada_alas(glm::vec3(-1.0,0.0,0.0));
	CurvaConstante torcion_alas(glm::vec3(0.0,1.0,0.0));
	ConjuntoPuntosAlas funcionConjuntoAlas;
	alas = new Barrido(&funcionConjuntoAlas, &curva_alas, &derivada_alas, &torcion_alas, 0.1, &material_cubo);

	SegmentoRecta curva_base(glm::vec3(0.0,0.0,0.0), glm::vec3(1.5,0.0,0.0));
	CurvaConstante derivada_base(glm::vec3(-1.0,0.0,0.0));
	ConjuntoPuntosBase funcionConjuntoBase;

	base = new Barrido(&funcionConjuntoBase, &curva_base, &derivada_base, &torcion_alas, 0.1, &material_cubo);

	cabina = new Barrido(
		&ConjuntoPuntosCabina(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(0.6,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		1.0,
		&material_cubo);

	techo = new Barrido(
		&ConjuntoPuntosTecho(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(0.9,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		0.1,
		&material_cubo
		);

	vidrio = new Barrido(
		&ConjuntoPuntosVidrio(),
		&SegmentoRecta(glm::vec3(0.6,0.0,0.0), glm::vec3(0.9,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		0.1,
		&material_color
		);
}

void NaveCombate::dibujar(const glm::mat4& m) {
	//superficie_barrido->dibujar(m);
	//cubo.dibujar(m);
	alas->dibujar(m);
	base->dibujar(m);
	cabina->dibujar(m);
	techo->dibujar(m);
	vidrio->dibujar(m);
}