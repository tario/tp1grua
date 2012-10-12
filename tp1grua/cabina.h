#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "cubo_color.h"

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

	private:

		CuboColor cubo;
		CuboColor contra_peso;

		glm::mat4 m_contra_peso;
};

#endif