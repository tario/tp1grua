#include "stdafx.h"
#include "anillo.h"
#include "segmento_recta.h"
#include "circunferencia.h"
#include "curva_constante.h"
#include "barrido.h"
#include "revolucion.h"

class ConjuntoPuntosAnilloColumna : public FuncionConjuntoPuntos { 
	public:
		std::vector<Punto> conjunto(float t) {
			std::vector<Punto> ret;
			float l=0.05;
			ret.push_back(Punto(l,l*2,Punto::NOSMOOTH));
			ret.push_back(Punto(-l,l*2,Punto::NOSMOOTH));
			ret.push_back(Punto(-l,-l*2,Punto::NOSMOOTH));
			ret.push_back(Punto(l,-l*2,Punto::NOSMOOTH));
			return ret;
		}
};

class ConjuntoPuntosAnilloToroide : public FuncionConjuntoPuntos { 
	public:
		ConjuntoPuntosAnilloToroide(float radio) : radio(radio) {};
		std::vector<Punto> conjunto(float t) {
			std::vector<Punto> ret;
			ret.push_back(Punto(radio,radio,Punto::SMOOTH));
			ret.push_back(Punto(-radio,radio,Punto::SMOOTH));
			ret.push_back(Punto(-radio,-radio,Punto::SMOOTH));
			ret.push_back(Punto(radio,-radio,Punto::SMOOTH));
			return closed_cubic_bspline(ret,32);
		}

private:
		float radio;
};

Anillo::Anillo(Material* material1, Material* material2) {
	toroide = new Revolucion(
		&ConjuntoPuntosAnilloToroide(0.1), 
		1.5,
		0.025,
		material2,
		0.0,1.0);

	toroideParcial = new Revolucion(
		&ConjuntoPuntosAnilloToroide(0.2), 
		1.5,
		0.025,
		material1,
		0.2,0.3,true);

	columnaCruzada = new Barrido(
		&ConjuntoPuntosAnilloColumna(),
		&SegmentoRecta(glm::vec3(2.0,-1.5,0.0), glm::vec3(2.0,1.5,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		1.0,
		material1,
		0.0,1.0,false);
	
	this->matriz_toroide = 
		glm::rotate(
				glm::translate(
					glm::mat4(1.0),
					glm::vec3(2.0,0.0,0.0)
				),
			90.0f, 
			glm::vec3(0.0,1.0,0.0)
		);
}

void Anillo::dibujar(const glm::mat4& m) {
	toroide->dibujar(m*matriz_toroide);
	toroideParcial->dibujar(m*matriz_toroide);

	static glm::mat4 rotate90 = glm::rotate(glm::mat4(1.0), 90.0f, glm::vec3(1.0,0.0,0.0));
	static glm::mat4 rotate180 = glm::rotate(glm::mat4(1.0), 180.0f, glm::vec3(1.0,0.0,0.0));
	static glm::mat4 rotate270 = glm::rotate(glm::mat4(1.0), 270.0f, glm::vec3(1.0,0.0,0.0));
	toroideParcial->dibujar(m*rotate90*matriz_toroide);
	toroideParcial->dibujar(m*rotate180*matriz_toroide);
	toroideParcial->dibujar(m*rotate270*matriz_toroide);

	columnaCruzada->dibujar(m);
	columnaCruzada->dibujar(m*rotate90);
}
