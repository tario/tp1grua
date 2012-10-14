#ifndef __GRUA_H
#define __GRUA_H

#include "dibujable.h"
#include "model_object.h"
#include "cabina.h"

class Grua : public Dibujable {
public:
	Grua();

	void dibujar(const glm::mat4& m);
	void girar_cabina(float angulo);
	void girar_brazo(float angulo);
	void longitud_cable(float delta);
private:

	ModelObject mo_torre;
	ModelObject mo_cabina;
	Cabina cabina;
	float angulo_cabina;

};

#endif

