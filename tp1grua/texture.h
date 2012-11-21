#ifndef __TEXTURE_H
#define __TEXTURE_H 

#include <fstream>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"

class Texture {
	public:

		Texture(const std::string& path);

		void load(int slot);

	private:
		int height;
		int width;
		GLuint textureid;
};

#endif
