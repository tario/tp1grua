#ifndef __FUNCION_CONJUNTO_PUNTOS_H
#define __FUNCION_CONJUNTO_PUNTOS_H

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class FuncionConjuntoPuntos {
	public:
		class Punto{
		public:
			Punto(float x, float y) : punto(x,y){
			}
			glm::vec2 punto;
		};

		virtual std::vector<Punto> conjunto(float t)=0;
		virtual ~FuncionConjuntoPuntos() {
		}
};

#endif
