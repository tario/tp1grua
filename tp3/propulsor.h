#ifndef __PROPULSOR_H
#define __PROPULSOR_H

#include "dibujable.h"
#include "material.h"
#include "barrido.h"
#include "material_color_solido.h"

class Propulsor : public Dibujable {
	public:
		Propulsor(Material* material, bool encendido=false);
		void dibujar(const glm::mat4& m);
	private:
		Barrido* propulsorPrisma1;
		Barrido* propulsorPrisma2;
		Material* material;
		MaterialColorSolido materialColorSolido;

		bool encendido;
};

#endif
