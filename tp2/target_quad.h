#ifndef __TARGET_OBJECT_H
#define __TARGET_OBJECT_H

#include "dibujable.h"
#include "material_color_solido.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "cubo_texturado.h"

class TargetQuad : public Dibujable  {
	public:
		TargetQuad();
		void dibujar(const glm::mat4& m);
	private:
		MaterialColorSolido material;
		GLuint vaoHandle;
		CuboTexturado cuboTexturado;
};

#endif
