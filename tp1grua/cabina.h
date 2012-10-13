#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "cubo_color.h"
#include "brazo.h" 

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

		void girar_brazo(float angulo);
	private:

		CuboColor cubo;
		CuboColor contra_peso;
		Brazo brazo;

		glm::mat4 m_contra_peso;
		glm::mat4 m_brazo;

		float angulo_brazo;
};

#endif
