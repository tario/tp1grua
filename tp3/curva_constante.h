#ifndef __CURVA_CONSTANTE_H
#define __CURVA_CONSTANTE_H

#include "curva.h"

class CurvaConstante: public Curva {
public:
	CurvaConstante(glm::vec3 origen);
	glm::vec3 punto(float t);

private:
	glm::vec3 origen;
};

#endif
