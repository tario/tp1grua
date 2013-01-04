#ifndef __ANILLO_H
#define __ANILLO_H

#include "dibujable.h"
#include "material.h"

class Anillo : public Dibujable {
	public:
		Anillo(Material* material1, Material* material2);
		void dibujar(const glm::mat4& m);

	private:
		Dibujable* toroide;
		Dibujable* toroideParcial;
		Dibujable* columnaCruzada;

		glm::mat4 matriz_toroide;
};

#endif
