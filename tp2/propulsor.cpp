#include "stdafx.h"
#include "propulsor.h"
#include "segmento_recta.h"
#include "curva_constante.h"
#include "circunferencia.h"

class ConjuntoPuntosPropulsorPrisma1 : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		for (int i=0;i<16;i++) {
			float angle = float(i)*6.28/16;
			float r=0.10;
			ret.push_back(Punto(cos(angle)*r,sin(angle)*r, Punto::SMOOTH));
		}
		return ret;
	}
};

class ConjuntoPuntosPropulsorPrisma2 : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		for (int i=0;i<16;i++) {
			float angle = float(i)*6.28/16;
			float r=0.12;
			ret.push_back(Punto(cos(angle)*r,sin(angle)*r, Punto::SMOOTH));
		}
		return ret;
	}
};

class ConjuntoPuntosPropulsorCoberturaPrisma : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> ret;
		float l = 0.1;
		ret.push_back(Punto(-0.01,-l));
		ret.push_back(Punto(0.01,-l));
		ret.push_back(Punto(0.01,0.0));
		ret.push_back(Punto(-0.01,0.0));
		return ret;
	}
};

Propulsor::Propulsor(Material* material) : material(material), materialColorSolido(glm::vec3(0.0,1.0,1.0),true) {
	propulsorPrisma2 = new Barrido(
		&ConjuntoPuntosPropulsorPrisma1(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(-0.1,0.0,0.0)),
		&CurvaConstante(glm::vec3(-1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		&materialColorSolido,
		0.0,0.4,true);

	/*coberturaPrisma =new Barrido(
		&ConjuntoPuntosPropulsorCoberturaPrisma(), 
		&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(0.0,1.0,0.0)),
		&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(0.0,0.0,1.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		&materialColorSolido,
		0.0,1.0,false);*/

propulsorPrisma1 =new Barrido(
		&ConjuntoPuntosPropulsorCoberturaPrisma(), 
		&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(0.0,0.11,0.0)),
		&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(0.0,0.0,-1.0)),
		&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0),glm::vec3(0.0,1.0,0.0)),
		0.05,
		material,
		0.0,1.0,false);
}

void Propulsor::dibujar(const glm::mat4& m) {
	material->use(m);

	//propulsorPrisma1->dibujar(m);
	//propulsorPrisma2->dibujar(m);
	propulsorPrisma2->dibujar(m);
	propulsorPrisma1->dibujar(m);
}