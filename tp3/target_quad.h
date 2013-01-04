#ifndef __TARGET_OBJECT_H
#define __TARGET_OBJECT_H

#include "dibujable.h"
#include "material_target_quad.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"

class TargetQuad : public Dibujable  {
	public:
		TargetQuad();
		void dibujar(const glm::mat4& m);
	private:
		MaterialTargetQuad material;
		GLuint vaoHandle;
};

#endif
