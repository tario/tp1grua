#ifndef __MOTOR_H
#define __MOTOR_H

#include "dibujable.h"
#include "barrido.h"
#include "material.h"
#include "propulsor.h"

class Motor : public Dibujable {
	public:
		Motor(Material* material1, Material* material3);
		void dibujar(const glm::mat4& m);

		static Motor* instance(Material* material1, Material* material3);
	private:
		Barrido* superficie;
		Propulsor* propulsor;

};

#endif
