// define un cubo de lado unitario centrado en el origen de coordenadas
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"

class Cubo {
	public:

		Cubo();

	protected:
		GLuint getVaoHandle() { return vaoHandle;};

	private:
		GLuint vaoHandle;
};

