#ifndef __ANILLO_H
#define __ANILLO_H

#include "dibujable.h"
#include "barrido.h"

class Anillo : public Dibujable {
	public:
		Anillo(Material* material1, Material* material2);
		void dibujar(const glm::mat4& m);

	private:
		Barrido* toroide;
		Barrido* toroideParcial;
		Barrido* columnaCruzada;
};

#endif
