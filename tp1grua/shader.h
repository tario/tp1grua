#ifndef _SHADER_H
#define _SHADER_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {

public:
	static glm::mat4 projectionMatrix;
	static glm::vec3 cameraDirection;
	// carga un programa dadas las rutas del shader de fragmento y shader de vertices
	Shader(std::string fragmentShader, std::string vertexShader);

	void link();
	void use();
	void bindAttribLocation(GLuint location, std::string attrib);
	int getUniformLocation(std::string attrib);

private:
	GLuint programHandle;

};

#endif
