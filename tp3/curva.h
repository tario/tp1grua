#ifndef __CURVA_H
#define __CURVA_H

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Curva {
	public:
		virtual glm::vec3 punto(float t)=0;
		virtual ~Curva() {
		}
};

#endif
