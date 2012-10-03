// define un cubo de lado unitario centrado en el origen de coordenadas
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "dibujable.h"

class Cubo : public Dibujable {
	public:

		Cubo();

	protected:
		GLuint getVaoHandle() { return vaoHandle;};
		GLuint vaoHandle;

	private:
};

