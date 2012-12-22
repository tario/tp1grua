#include "stdafx.h"
#include "nave_nodriza.h"
#include "null_texture.h"
#include "segmento_recta.h"
#include "curva_constante.h"

class ConjuntoPuntosCilindroCentral : public FuncionConjuntoPuntos {
	public:
		std::vector<Punto> conjunto(float t) { 
			std::vector<Punto> ret;
			float r = 0.12;
			for (int i=0;i<32;i++) {
				float angle = float(i)*6.28/32;
				ret.push_back(Punto(cos(angle)*r,sin(angle)*r,Punto::SMOOTH));
			}
			return ret;
		}
};

class ConjuntoPuntosPuenteCentral : public FuncionConjuntoPuntos {
	public:
		std::vector<Punto> conjunto(float t) { 
			std::vector<Punto> curva1, curva2, bezier1, bezier2, ret;

			float size = 3.0 * t * (1.0 -t) + 0.8;

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
		}
};

NaveNodriza::NaveNodriza(Texture* reflectionMap) : 
	textura_nave("shiphull.bmp"),
	normal_nave("shiphull_normal2.bmp"),
	material1(&textura_nave, &normal_nave, NullTexture::instance()),
	material2(&textura_nave, NullTexture::instance(), reflectionMap),
	material3(glm::vec3(0.25,0.25,0.25),true),
	anillo(&material1, &material2)
{
	material1.kaSetter->set(0.00);
	material1.kdSetter->set(1.5);
	material1.ksSetter->set(0.05);
	material1.intensidadRelieveSetter->set(1.0);
	material1.intensidadDifusoSetter->set(0.6);

	material2.kaSetter->set(0.05);
	material2.ksSetter->set(0.5);
	material2.kdSetter->set(1.5);
	material2.intensidadDifusoSetter->set(0.0);
	material2.intensidadGrisSetter->set(0.7);
	material2.intensidadReflexionSetter->set(0.7);

	motor = Motor::instance(&material1, &material3);

	cilindroCentral = new Barrido(
		&ConjuntoPuntosCilindroCentral(), 
		&SegmentoRecta(glm::vec3(1.0,0.0,0.0),glm::vec3(3.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		1.0,
		&material1,
		0.0,1.0);

	puenteCentral = new Barrido(
		&ConjuntoPuntosPuenteCentral(), 
		&SegmentoRecta(glm::vec3(3.0,0.0,0.0),glm::vec3(4.5,0.0,0.0)),
		&CurvaConstante(glm::vec3(1.0,0.0,0.0)),
		&CurvaConstante(glm::vec3(0.0,1.0,0.0)),
		0.05,
		&material1,
		0.0,1.0);

	rotacion_anillo = glm::mat4(1.0);
}
static glm::mat4 desplazamiento = glm::translate(glm::mat4(1.0), glm::vec3(-2.25,0.0,0.0));
void NaveNodriza::dibujar(const glm::mat4& m) {
	motor->dibujar(m * desplazamiento);
	cilindroCentral->dibujar(m * desplazamiento);
	puenteCentral->dibujar(m * desplazamiento);

	rotacion_anillo = glm::rotate(rotacion_anillo, 0.7f, glm::vec3(1.0,0.0,0.0));
	anillo.dibujar(m * desplazamiento * rotacion_anillo);
}