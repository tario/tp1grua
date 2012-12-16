#ifndef __NAVE_COMBATE_H
#define __NAVE_COMBATE_H

#include "dibujable.h"
#include "material_color_solido.h"
#include "cubo_texturado.h"

class NaveCombate : public Dibujable {
	public:

		NaveCombate();
		void dibujar(const glm::mat4&);

	private:
		CuboTexturado cubo;
		MaterialColorSolido material_cubo;
};

#endif
