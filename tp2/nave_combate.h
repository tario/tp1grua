#ifndef __NAVE_COMBATE_H
#define __NAVE_COMBATE_H

#include "dibujable.h"
#include "material_tp3.h"
#include "null_texture.h"
#include "bitmap_texture.h"
#include "material_color_solido.h"
#include "barrido.h"
#include "misil.h"

class NaveCombate : public Dibujable {
	public:

		NaveCombate(Texture* mapa_reflexion_universo = NullTexture::instance());
		void dibujar(const glm::mat4&);

	private:
		MaterialTP3 material_reflejante;
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
