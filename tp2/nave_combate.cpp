#include "stdafx.h"
#include "nave_combate.h"
#include "segmento_recta.h"
#include "curva_constante.h" 

class ConjuntoPuntos : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		ret.push_back(Punto(-0.5,0.5));
		ret.push_back(Punto(-0.5,-0.5));
		ret.push_back(Punto(0.5,-0.5));
		ret.push_back(Punto(0.5,0.5));
		return ret;
	};
};

class ConjuntoPuntosAlas : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		if (t<0.1) {
		ret.push_back(Punto(-5.0*(t+0.1),-0.05));
		ret.push_back(Punto(0.0,-0.1));
		ret.push_back(Punto(5.0*(t+0.1),-0.05));
		ret.push_back(Punto(0.0,0.0));
		} else {
		ret.push_back(Punto(-1.0+(t-0.1)*0.2,-0.05));
		ret.push_back(Punto(0.0,-0.1));
		ret.push_back(Punto(1.0-(t-0.1)*0.2,-0.05));
		ret.push_back(Punto(0.0,0.0));
		}

		return ret;
	};
};


class ConjuntoPuntosBase : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		if (t<0.4) {
		ret.push_back(Punto(-0.4,0.1));
		ret.push_back(Punto(-0.25,-0.1));
		ret.push_back(Punto(0.25,-0.1));
		ret.push_back(Punto(0.4,0.1));
		} else {
		ret.push_back(Punto(-0.4+(t-0.4)*0.4,-(-0.1+(t-0.4)*0.1/0.6)));
		ret.push_back(Punto(-0.25+(t-0.4)*0.09/0.6,-(0.1-(t-0.4)*0.1/0.6)));
		ret.push_back(Punto(0.25-(t-0.4)*0.09/0.6,-(0.1-(t-0.4)*0.1/0.6)));
		ret.push_back(Punto(0.4-(t-0.4)*0.4,-(-0.1+(t-0.4)*0.1/0.6)));
		}
		ret = bezier(ret,8);
		if (t<0.4) {
			ret.push_back(Punto(0.4,0.1));
		} else {
			ret.push_back(Punto(0.4-(t-0.4)*0.4,-(-0.1+(t-0.4)*0.1/0.6)));
		}

		ret.at(0).normalMode = Punto::NOSMOOTH;
		return ret;
	};
};
class ConjuntoPuntosCabina : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		ret.push_back(Punto(0.4,0.1));
		ret.push_back(Punto(0.25,0.2+t*0.1));
		ret.push_back(Punto(-0.25,0.2+t*0.1));
		ret.push_back(Punto(-0.4,0.1));

		return ret;
	};
};
class ConjuntoPuntosTecho : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		if (t<0.4) {
		ret.push_back(Punto(0.25,0.2+t*0.1));
		ret.push_back(Punto(0.22,0.225+t*0.1));
		ret.push_back(Punto(-0.22,0.225+t*0.1));
		ret.push_back(Punto(-0.25,0.2+t*0.1));
		} else {
		ret.push_back(Punto(0.25,0.24-(t-0.4)*0.1));
		ret.push_back(Punto(0.22,0.265-(t-0.4)*0.225));
		ret.push_back(Punto(-0.22,0.265-(t-0.4)*0.225));
		ret.push_back(Punto(-0.25,0.24-(t-0.4)*0.1));
		}
		return ret;
	};
};
class ConjuntoPuntosVidrio : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		
		if (t<0.6) {
		ret.push_back(Punto(0.4-(t-0.4)*0.4,0.1-(t-0.4)*0.1/0.6));
		ret.push_back(Punto(0.25,0.24-(t-0.4)*0.1));
		ret.push_back(Punto(-0.25,0.24-(t-0.4)*0.1));
		ret.push_back(Punto(-0.4+(t-0.4)*0.4,0.1-(t-0.4)*0.1/0.6));
		} else {
		ret.push_back(Punto(0.4-(t-0.4)*0.4,0.1-(t-0.4)*0.1/0.6));
		ret.push_back(Punto(0.25,0.22-(t-0.6)*1.5333));
		ret.push_back(Punto(-0.25,0.22-(t-0.6)*1.5333));
		ret.push_back(Punto(-0.4+(t-0.4)*0.4,0.1-(t-0.4)*0.1/0.6));
		}
		return ret;
	};
};


NaveCombate::NaveCombate(Texture* mapa_reflexion_universo) : 
	mapa_difuso_nave("nave.bmp"),
	material_reflejante(&mapa_difuso_nave, mapa_reflexion_universo),
	material_color(glm::vec3(0.0,0.0,0.0)) {

		material_reflejante.ksSetter->set(0.2);
		material_reflejante.kdSetter->set(1.5);
		material_reflejante.intensidadDifusoSetter->set(0.6);
		material_reflejante.intensidadReflexionSetter->set(0.2);
		material_reflejante.kaSetter->set(0.1);
		material_reflejante.glossinessSetter->set(9.0);


	SegmentoRecta curva_alas(glm::vec3(0.525,0.0,0.0), glm::vec3(0.025,0.0,0.0));
	CurvaConstante derivada_alas(glm::vec3(-1.0,0.0,0.0));
	CurvaConstante torcion_alas(glm::vec3(0.0,1.0,0.0));
	ConjuntoPuntosAlas funcionConjuntoAlas;
	alas = new Barrido(&funcionConjuntoAlas, &curva_alas, &derivada_alas, &torcion_alas, 0.1, &material_reflejante);

	SegmentoRecta curva_base(glm::vec3(0.0,0.0,0.0), glm::vec3(1.5,0.0,0.0));
	CurvaConstante derivada_base(glm::vec3(1.0,0.0,0.0));
	ConjuntoPuntosBase funcionConjuntoBase;

	base = new Barrido(&funcionConjuntoBase, &curva_base, &derivada_base, &torcion_alas, 0.1, &material_reflejante);

	cabina = new Barrido(
		&ConjuntoPuntosCabina(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(1.5,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		1.0,
		&material_reflejante,
		0.0,0.4);

	techo = new Barrido(
		&ConjuntoPuntosTecho(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(1.5,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		0.1,
		&material_reflejante,
		0.0,0.6);

	vidrio = new Barrido(
		&ConjuntoPuntosVidrio(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(1.5,0.0,0.0)),
		&derivada_base,
		&torcion_alas,
		0.1,
		&material_reflejante,
		0.4,0.7);

	misil = Misil::instance();
}

void NaveCombate::dibujar(const glm::mat4& m) {
	glm::mat4 m2 = glm::translate(m, glm::vec3(-0.75,0.0,0.0));

	alas->dibujar(m2);
	base->dibujar(m2);
	cabina->dibujar(m2);
	techo->dibujar(m2);
	vidrio->dibujar(m2);

	misil->dibujar(glm::translate(m2, glm::vec3(0.2, 0.6, -0.02)));
	misil->dibujar(glm::translate(m2, glm::vec3(0.2, -0.6, -0.02)));
}