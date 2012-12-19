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
			typedef enum {
				NOSMOOTH,
				SMOOTH
			} NormalMode ;

			Punto(float x, float y, NormalMode normalMode = NOSMOOTH) : punto(x,y), normalMode(normalMode) {
			}
			glm::vec2 punto;
			NormalMode normalMode;
		};

		virtual std::vector<Punto> conjunto(float t)=0;
		virtual ~FuncionConjuntoPuntos() {
		}
};

#endif
