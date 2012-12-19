#include "stdafx.h"
#include "misil.h"
#include "segmento_recta.h"
#include "curva_constante.h"

class ConjuntoPuntosCuerpo : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;

		float d = 0.05;
		if (t > 0.8) {
			d = 0.05 - (t-0.8)*0.25;
		}

		for (t=0.0; t<6.14; t+=0.614){
			ret.push_back(Punto(cos(t)*d,sin(t)*d, Punto::SMOOTH));
		}
		return ret;
	};
};

class ConjuntoPuntosAlasMisil : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		ret.push_back(Punto(0.0,-0.01));
		ret.push_back(Punto(0.8*(t*0.2/0.3-0.2), 0.0));
		ret.push_back(Punto(0.0, 0.01));
		ret.push_back(Punto(-0.8*(t*0.2/0.3-0.2), 0.0));
		return ret;
	};
};

Misil::Misil() : material(glm::vec3(0.2,0.2,0.2), true) {
	CurvaConstante torcion(glm::vec3(0.0,1.0,0.0));

	cuerpo = new Barrido(
		&ConjuntoPuntosCuerpo(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(0.5,0.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		&torcion,
		0.1,
		&material,
		0.0,1.0			
		);

	alas = new Barrido(
		&ConjuntoPuntosAlasMisil(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(0.5,0.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		&torcion,
		1.0,
		&material,
		0.025,0.3	
		);
}

void Misil::dibujar(const glm::mat4& m) {
	cuerpo->dibujar(m);
	alas->dibujar(m);
}

Misil* Misil::instance() {
	static Misil misil;
	return &misil;
}
