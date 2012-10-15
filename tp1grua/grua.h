#ifndef __GRUA_H
#define __GRUA_H

#include "dibujable.h"
#include "model_object.h"
#include "cabina.h"
#include "torre.h"

class Grua : public Dibujable {
public:
	Grua();

	void dibujar(const glm::mat4& m);
	void girar_cabina(float angulo);
	void girar_brazo(float angulo);
	void longitud_cable(float delta);

	void cambiar_suciedad(float delta_suciedad);
private:

	ModelObject mo_torre;
	ModelObject mo_cabina;
	Cabina cabina;
	Torre torre;
	float angulo_cabina;
	float _suciedad;

};

#endif

