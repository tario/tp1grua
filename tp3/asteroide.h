#ifndef __ASTEROIDE_H
#define __ASTEROIDE_H

#include "dibujable.h"
#include "barrido.h"

class Asteroide : public Dibujable {
	public:
		Asteroide();
		void dibujar(const glm::mat4& m);
	private:
		static Material* materialAsteroide;
		Barrido* cuerpo;
};

#endif
