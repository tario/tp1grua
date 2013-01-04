#ifndef __NAVE_COMBATE_H
#define __NAVE_COMBATE_H

#include "dibujable.h"
#include "null_texture.h"
#include "bitmap_texture.h"
#include "material_color_solido.h"
#include "material_difuso_reflexion.h"
#include "barrido.h"
#include "misil.h"

class NaveCombate : public Dibujable {
	public:

		NaveCombate(Texture* mapa_reflexion_universo = NullTexture::instance());
		void dibujar(const glm::mat4&);

	private:
		MaterialDifusoReflexion material_reflejante;
		MaterialColorSolido material_color;

		BitmapTexture mapa_difuso_nave;
		Barrido* superficie_barrido;
		Barrido* alas;
		Barrido* base;
		Barrido* cabina;
		Barrido* techo;
		Barrido* vidrio;

		Misil* misil;

};

#endif