#include "stdafx.h"
#include "motor.h"
#include "segmento_recta.h"
#include "curva_constante.h" 

class ConjuntoPuntosMotor : public FuncionConjuntoPuntos {
	public:
	std::vector<Punto> conjunto(float t) {
		std::vector<Punto> curva1, curva2, bezier1, bezier2, ret;

		float size = 2.0 * t * (1.0 -t) + 1.6;

		curva1.push_back(Punto(-0.3*size,0.0));
		curva1.push_back(Punto(-0.35*size,-0.25*size));
		curva1.push_back(Punto(0.35*size,-0.25*size));
		curva1.push_back(Punto(0.3*size,0.0));

		curva2.push_back(Punto(0.3*size,0.0));
		curva2.push_back(Punto(0.25*size,0.4*size));
		curva2.push_back(Punto(-0.25*size,0.4*size));
		curva2.push_back(Punto(-0.3*size,0.0));
		bezier1 = bezier(curva1,16);
		bezier2 = bezier(curva2,16);
		ret.insert(ret.end(),bezier1.begin(),bezier1.end());
		ret.insert(ret.end(),bezier2.begin(),bezier2.end());
		return ret;
	};
};

Motor::Motor(Material* material1, Material* material3) {
	superficie = new Barrido(
		&ConjuntoPuntosMotor(), 
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0),glm::vec3(1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		0.05,
		material1,
		0.0,1.0);

	propulsor = new Propulsor(material3);
}
void Motor::dibujar(const glm::mat4& m) {
	superficie->dibujar(m);

	propulsor->dibujar(glm::translate(m,glm::vec3(0.0,0.0,0.2)));
	propulsor->dibujar(glm::translate(m,glm::vec3(0.0,0.2,0.0)));
	propulsor->dibujar(glm::translate(m,glm::vec3(0.0,-0.2,0.0)));
}

Motor* Motor::instance(Material* material1, Material* material3) {
	static Motor* motor = 0;
	if (motor==0)
		motor = new Motor(material1,material3);

	return motor;
}

