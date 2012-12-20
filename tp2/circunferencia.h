#ifndef __CIRCUNFERENCIA_H
#define __CIRCUNFERENCIA_H

#include "curva.h"

class Circunferencia: public Curva {
public:
	Circunferencia(glm::vec3 centro, glm::vec3 eje, glm::vec3 rotation_vector);
	glm::vec3 punto(float t);

private:
	glm::vec3 centro;
	glm::vec3 eje;
	glm::vec3 rotation_vector;
};

#endif
