#include "stdafx.h"
#include "asteroide.h"
#include "material_textura.h"
#include "bitmap_texture.h"
#include "segmento_recta.h"
#include "curva_constante.h"
#include "material_difuso_relieve.h" 
#include "null_texture.h"
#include <algorithm>

Material* Asteroide::materialAsteroide = 0;

bool comparador_puntos(FuncionConjuntoPuntos::Punto p0, FuncionConjuntoPuntos::Punto p1) {
	return glm::angle(p0.punto, glm::vec2(1.0,0.0)) < glm::angle(p1.punto, glm::vec2(1.0,0.0));
}

#define ASTEROIDE_DEFORMIDAD 0.6
#define ASTEROIDE_PICOS 7

class ConjuntoPuntosCuerpoAsteroide : public FuncionConjuntoPuntos {
	public:

		ConjuntoPuntosCuerpoAsteroide() {
			a.push_back(rand() % 1000 / 5000.0 + 0.1);
			b.push_back(rand() % 1000 / 5000.0 + 0.1);
			c.push_back(rand() % 1000 / 5000.0 + 0.1);
			for (int i=1; i<8; i++){
				a.push_back(a.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
				b.push_back(b.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
				c.push_back(c.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
			}
		}

		std::vector<Punto> conjunto(float t) {
			std::vector<Punto> ret;
			float d = sqrt(0.25-(t-0.5)*(t-0.5));
			Punto pi( (cos(0.0)+a[0] )*d*0.5, (sin(0.0) + b[0])*d*0.5, Punto::SMOOTH);

			ret.push_back(pi);
			for (int i=1; i<8; i++){
				float t2 = i * 6.28/ 8 ;
				float d = sqrt(0.25-(t-0.5)*(t-0.5));

				if (rand() % ASTEROIDE_PICOS == 1) {
					d = d * (rand() % 25 + 40) * 0.025;
				}

				Punto p( (cos(t2)+a[i]*ASTEROIDE_DEFORMIDAD)*d*0.5, (sin(t2)+b[i]*ASTEROIDE_DEFORMIDAD)*d*0.5, Punto::SMOOTH);
				ret.push_back(p);
			}
			ret.push_back(pi);

			return bezier(ret,32);
		};

	private:

		std::vector<float> c, b, a;

};

Asteroide::Asteroide() {
	if (Asteroide::materialAsteroide==0) {
		MaterialDifusoRelieve* material_asteroide = 
			new MaterialDifusoRelieve(
				new BitmapTexture("lunar.bmp"), 
				new BitmapTexture("asteroid_normals.bmp")
				);
		material_asteroide->kaSetter->set(0.0);
		material_asteroide->kdSetter->set(1.5);
		material_asteroide->ksSetter->set(0.05);
		material_asteroide->intensidadDifusoSetter->set(1.0);
		material_asteroide->intensidadRelieveSetter->set(0.5);

		Asteroide::materialAsteroide = material_asteroide;
	}
	CurvaConstante torcion(glm::vec3(0.0,1.0,0.0));
	cuerpo = new Barrido(
		&ConjuntoPuntosCuerpoAsteroide(),
		&SegmentoRecta(glm::vec3(0.0,0.0,-0.25), glm::vec3(0.0,0.0,0.25)),
		&CurvaConstante(glm::vec3(0.0,0.0,1.0)),
		&torcion,
		0.05,
		materialAsteroide,
		0.0,1.0			
		);
}

void Asteroide::dibujar(const glm::mat4& m){
	cuerpo->dibujar(m);
}
