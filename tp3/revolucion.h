#ifndef __REVOLUCION_H
#define __REVOLUCION_H

#include "barrido.h"

class Revolucion : public Dibujable {
	public:
		Revolucion(
				FuncionConjuntoPuntos* funcionConjuntoPuntos,
				float radio,
				float h,
				Material* material,
				float t_inicial=0.0, float t_final=1.0, bool texture_scaling = false
			);

		void dibujar(const glm::mat4& m);
	private:
		Barrido barrido;
};

#endif
