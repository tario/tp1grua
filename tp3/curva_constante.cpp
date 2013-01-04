#include "stdafx.h"
#include "curva_constante.h"

CurvaConstante::CurvaConstante(glm::vec3 origen) :
origen(origen) {

}

glm::vec3 CurvaConstante::punto(float t){
	return origen;
}
