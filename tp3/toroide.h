#ifndef __TOROIDE_H
#define __TOROIDE_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "dibujable.h"
#include "material.h"

class Toroide : public Dibujable {
	public:
		Toroide(Material* material, float section_ratio, int geometric_detail = 20);
		void dibujar(const glm::mat4& m);
	protected:
		
		GLuint getVaoHandle() { return vaoHandle;};
		GLuint vaoHandle;

	private:
		Material* material;
		int cantidadVertices;
};

#endif
