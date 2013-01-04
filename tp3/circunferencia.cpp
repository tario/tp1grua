#include "stdafx.h"
#include "circunferencia.h"

Circunferencia::Circunferencia(glm::vec3 centro, glm::vec3 eje, glm::vec3 rotation_vector) :
centro(centro),
eje(eje),
rotation_vector(rotation_vector) {

}

// t es de 0 a 1 y se interpreta como un angulo de 0 a 360
glm::vec3 Circunferencia::punto(float t) {
	return centro + glm::vec3(glm::rotate(glm::mat4(1.0), t*360.0f, eje) * glm::vec4(rotation_vector,1.0));
}