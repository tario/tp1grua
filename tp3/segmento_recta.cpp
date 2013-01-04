#include "stdafx.h"
#include "segmento_recta.h"

SegmentoRecta::SegmentoRecta(glm::vec3 origen, glm::vec3 destino) :
origen(origen), destino(destino) {

}

glm::vec3 SegmentoRecta::punto(float t){
	return origen * (1-t) + destino * t;
}
