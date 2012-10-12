#ifndef __GRUA_H
#define __GRUA_H

#include "dibujable.h"
#include "model_object.h"

class Grua : public Dibujable {
public:
	Grua();

	void dibujar(const glm::mat4& m);
	void girar_cabina(float angulo);
private:

	ModelObject torre;
	ModelObject cabina;
	float angulo_cabina;
};

#endif

