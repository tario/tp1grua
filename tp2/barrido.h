#ifndef __BARRIDO_H
#define __BARRIDO_H

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "curva.h"
#include "funcion_conjunto_puntos.h"
#include "dibujable.h"
#include "material.h"

class Barrido : public Dibujable {
	public:
		class Punto {
			public:
				glm::vec2 posicion;
		};

		// la superficie de barrido toma como parametro
		// una funcion de devuelve una nube de puntos para
		// cada real entre 0 y 1
		// y una curva que devuelve un punto en el espacio y una orientacion para cada 
		// valor real entre 0 y 1
		Barrido(
				FuncionConjuntoPuntos* funcionConjuntoPuntos,
				Curva* trayectoria,
				Curva* derivada,
				Curva* torcion,
				float h,
				Material* material
			);

		void dibujar(const glm::mat4& m);

	private:
		GLuint getVaoHandle() { return vaoHandle;};
		GLuint vaoHandle;

		int cantidadVertices;
		Material* material;
};

#endif