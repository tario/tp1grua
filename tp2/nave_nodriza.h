#ifndef __NAVE_NODRIZA_H
#define __NAVE_NODRIZA_H

#include "dibujable.h"
#include "material_tp3.h"
#include "material_color_solido.h"
#include "material_color_reflexion.h"
#include "material_difuso_relieve.h"
#include "motor.h"
#include "bitmap_texture.h"
#include "barrido.h"
#include "anillo.h"

class NaveNodriza : public Dibujable { 
	public:

		NaveNodriza(Texture* reflectionMap);
		void dibujar(const glm::mat4& m);

	private:
		Motor* motor;
		BitmapTexture textura_nave;
		BitmapTexture normal_nave;
		MaterialColorSolido material3;
		MaterialColorReflexion material2;
		MaterialDifusoRelieve material1;

		Barrido* cilindroCentral;
		Barrido* puenteCentral;
		Anillo anillo;

		glm::mat4 rotacion_anillo;
};

#endif
