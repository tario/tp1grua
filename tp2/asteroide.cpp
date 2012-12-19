#include "stdafx.h"
#include "asteroide.h"
#include "material_textura.h"
#include "bitmap_texture.h"
#include "segmento_recta.h"
#include "curva_constante.h"
#include "material_tp3.h" 
#include "null_texture.h"
#include <algorithm>

Material* Asteroide::materialAsteroide = 0;

bool comparador_puntos(FuncionConjuntoPuntos::Punto p0, FuncionConjuntoPuntos::Punto p1) {
	return glm::angle(p0.punto, glm::vec2(1.0,0.0)) < glm::angle(p1.punto, glm::vec2(1.0,0.0));
}

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
			for (int i=0; i<8; i++){
				float t2 = i * 6.28/ 8;
				float d = sqrt(0.25-(t-0.5)*(t-0.5));

				if (rand() % 4 == 1) {
					d = d * (rand() % 15 + 40) * 0.025;
				}

				ret.push_back(Punto( (cos(t2)+a[i] )*d*0.5, (sin(t2) + b[i])*d*0.5, Punto::SMOOTH));
			}

			return ret;
		};

	private:

		std::vector<float> c, b, a;

};

Asteroide::Asteroide() {
	if (Asteroide::materialAsteroide==0) {
		MaterialTP3* materialtp3 = new MaterialTP3(new BitmapTexture("lunar.bmp"), NullTexture::instance(),NullTexture::instance());
		materialtp3->kaSetter->set(0.1);
		materialtp3->kdSetter->set(0.9);
		materialtp3->ksSetter->set(0.0);
		materialtp3->intensidadDifusoSetter->set(1.0);
		materialtp3->intensidadGrisSetter->set(0.0);
		materialtp3->intensidadRelieveSetter->set(0.0);
		materialtp3->intensidadReflexionSetter->set(0.0);

		Asteroide::materialAsteroide = materialtp3;
	}
	CurvaConstante torcion(glm::vec3(0.0,1.0,0.0));
	cuerpo = new Barrido(
		&ConjuntoPuntosCuerpoAsteroide(),
		&SegmentoRecta(glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,0.0,0.5)),
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
