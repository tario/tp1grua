#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "glm/glm.hpp"

class Material {
	public:
		virtual void use(const glm::mat4& m)=0;
};

#endif
