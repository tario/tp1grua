#include "stdafx.h" 
#include "esfera.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class ConjuntoPuntosSeccionEsfera : public FuncionConjuntoPuntos {
	public:
		ConjuntoPuntosSeccionEsfera(int vertices) : vertices(vertices) {};

		std::vector<Punto> conjunto(float t) {
			std::vector<Punto> ret;
			for (int i=0;i<vertices+1;i++) {
				float angle = float(i)*3.1415926536/vertices;
				ret.push_back(Punto(sin(angle)*0.5,-cos(angle)*0.5,Punto::SMOOTH));
			}

			return ret;
		}

		int vertices;
};

static glm::vec4 getvec4(float* data) {
	return glm::vec4(data[0],data[1],data[2],1.0);
}

Esfera::Esfera(Material* material, int geometric_detail, bool mirrorTexture) :
	revolucion(
		&ConjuntoPuntosSeccionEsfera(geometric_detail),
		0.0,
		1.0/geometric_detail,
		material,
		0.0,1.0
	) {
}

void Esfera::dibujar(const glm::mat4& m) {
	revolucion.dibujar(m);
}
