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
#include <vector>
#include "shader_program.h"

class Shader {

public:
	class Setter {
		public:
			virtual void apply()=0;
	};
	template <class T>
	class ConcreteSetter : public Setter {
		public:
			ConcreteSetter(int index) : index(index) {};
			ConcreteSetter<T>* set(const T& _x) { this->x = _x; return this; };
			void apply();
			T get();
		private:
			T x;
			int index;
	};

	static glm::mat4 projectionMatrix;
	static glm::vec3 cameraDirection;
	static glm::vec3 cameraPosition;

	// carga un programa dadas las rutas del shader de fragmento y shader de vertices
	Shader(ShaderProgram* shaderProgram);

	void use();

	template<class T>
	ConcreteSetter<T>* setter(const std::string& attrib) {
		ConcreteSetter<T>* s = new ConcreteSetter<T>(shaderProgram->getUniformLocation(attrib));
		setters.push_back(s);
		return s;
	}

	static glm::mat4 compute_normal_matrix(const glm::mat4& m);
private:

	ShaderProgram* shaderProgram;
	std::vector<Setter*> setters;

};

#endif
