#ifndef __MISIL_H
#define __MISIL_H

#include "dibujable.h"
#include "barrido.h"
#include "material_color_solido.h"
#include "propulsor.h" 

class Misil : public Dibujable {
	public:
		Misil(bool encendido = false);
		void dibujar(const glm::mat4& m);

		static Misil* instance();
	private:
		Barrido* cuerpo;
		Barrido* alas;
		Propulsor* propulsor;

		MaterialColorSolido material;

		bool encendido;
};

#endif
