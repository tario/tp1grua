#ifndef __CURVA_BEZIER_H
#define __CURVA_BEZIER_H

#include "dibujable.h"
#include "material_target_quad.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "funcion_conjunto_puntos.h"

class CurvaBezier : public Dibujable  {
	public:
		CurvaBezier();
		void dibujar(const glm::mat4& m);
	
		void actualizar_puntos_de_control(const std::vector<glm::vec3>& v);
	private:
		void actualizar_puntos(const std::vector<glm::vec3>& v);

		MaterialTargetQuad material;
		GLuint vaoHandle;
		GLuint positionBufferHandle;

		int cantidadVertices;
};

#endif
