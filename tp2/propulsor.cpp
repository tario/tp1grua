#include "stdafx.h"
#include "propulsor.h"
#include "segmento_recta.h"
#include "curva_constante.h"

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

Propulsor::Propulsor(Material* material) : material(material), materialColorSolido(glm::vec3(0.0,1.0,1.0),false) {

	propulsorPrisma1 = new Barrido(
		&ConjuntoPuntosPropulsorPrisma1(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(-0.1,0.0,0.0)),
		&CurvaConstante(glm::vec3(-1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		material,
		0.4,1.0,false);

	propulsorPrisma2 = new Barrido(
		&ConjuntoPuntosPropulsorPrisma2(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(-0.1,0.0,0.0)),
		&CurvaConstante(glm::vec3(-1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		material,
		0.0,1.0,false);

	propulsorPrisma3 = new Barrido(
		&ConjuntoPuntosPropulsorPrisma1(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(-0.1,0.0,0.0)),
		&CurvaConstante(glm::vec3(-1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		&materialColorSolido,
		0.0,0.4,true);
}

void Propulsor::dibujar(const glm::mat4& m) {
	material->use(m);

	propulsorPrisma1->dibujar(m);
	propulsorPrisma2->dibujar(m);
	propulsorPrisma3->dibujar(m);
}