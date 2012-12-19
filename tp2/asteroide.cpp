#include "stdafx.h"
#include "asteroide.h"
#include "material_textura.h"
#include "bitmap_texture.h"
#include "segmento_recta.h"
#include "curva_constante.h"

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
			for (int i=1; i<16; i++){
				a.push_back(a.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
				b.push_back(b.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
				c.push_back(c.at(i-1) + rand() % 1000 / 5000.0 - 0.1);
			}
		}

		std::vector<Punto> conjunto(float t) {
			std::vector<Punto> ret;

			//for (int i=0; i++; i<16) {
			//	ret.push_back(Punto(float(rand() % 1000) / 1000.0 - 0.5, float(rand() % 1000) / 1000.0 - 0.5));
			//}



			for (int i=0; i<16; i++){
				float t2 = i * 6.28/ 16;
				float d = sqrt(0.25-(t-0.5)*(t-0.5));

				if (rand() % 4 == 1) {
					d = d * (rand() % 15 + 40) * 0.025;
				}

				ret.push_back(Punto( (cos(t2)+a[i] )*d*0.5, (sin(t2) + b[i])*d*0.5));
			}

			//std::sort(ret.begin(), ret.end(), comparador_puntos);

			return ret;
		};

	private:

		std::vector<float> c, b, a;

};

Asteroide::Asteroide() {
	if (Asteroide::materialAsteroide==0) {
		Asteroide::materialAsteroide = new MaterialTextura(new BitmapTexture("lunar.bmp"));
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
