// define un cubo de lado unitario centrado en el origen de coordenadas
#ifndef __CUBO_H
#define __CUBO_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "dibujable.h"

class Cubo : public Dibujable {
public:
		int lastIndex () {
			return 2;
		}
	protected:
		Cubo(bool cara_superior=true);

		GLuint getVaoHandle() { return vaoHandle;};
		GLuint vaoHandle;

	private:
};

#endif
