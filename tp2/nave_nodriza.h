#ifndef __NAVE_NODRIZA_H
#define __NAVE_NODRIZA_H

#include "dibujable.h"
#include "material_tp3.h"
#include "material_color_solido.h"
#include "motor.h"
#include "bitmap_texture.h"

class NaveNodriza : public Dibujable { 
	public:

		NaveNodriza();
		void dibujar(const glm::mat4& m);

	private:
		Motor* motor;
		BitmapTexture textura_nave;
		MaterialColorSolido material3;
		MaterialTP3 material2;
		MaterialTP3 material1;
};

#endif
