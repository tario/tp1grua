#ifndef __SEGMENTO_RECTA_H
#define __SEGMENTO_RECTA_H

#include "curva.h"

class SegmentoRecta : public Curva {
public:
	SegmentoRecta(glm::vec3 origen, glm::vec3 destino);
	glm::vec3 punto(float t);

private:
	glm::vec3 origen, destino;
};

#endif
