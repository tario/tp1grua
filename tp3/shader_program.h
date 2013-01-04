#ifndef __SHADER_PROGRAM_H
#define __SHADER_PROGRAM_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

class ShaderProgram {
	public:
		ShaderProgram(std::string fragmentShader, std::string vertexShader);

		void link();
		void use();
		void bindAttribLocation(GLuint location, std::string attrib);
		int getUniformLocation(const std::string& attrib);

	private:
		GLuint programHandle;
};

#endif
