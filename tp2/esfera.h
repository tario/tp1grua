#ifndef __ESFERA_H
#define __ESFERA_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "dibujable.h"
#include "material.h"

class Esfera : public Dibujable {
	public:
		Esfera(Material* material, int geometric_detail = 20, bool mirrorTexture = false);
		void dibujar(const glm::mat4& m);
	protected:
		
		GLuint getVaoHandle() { return vaoHandle;};
		GLuint vaoHandle;

	private:
		Material* material;
		int cantidadVertices;
};

#endif
