#ifndef __NAVE_COMBATE_H
#define __NAVE_COMBATE_H

#include "dibujable.h"
#include "material_tp3.h"
#include "cubo_texturado.h"
#include "null_texture.h"
#include "bitmap_texture.h"

#include "barrido.h"

class NaveCombate : public Dibujable {
	public:

		NaveCombate(Texture* mapa_reflexion_universo = NullTexture::instance());
		void dibujar(const glm::mat4&);

	private:
		CuboTexturado cubo;
		MaterialTP3 material_cubo;

		BitmapTexture mapa_difuso_nave;
		Barrido* superficie_barrido;
		Barrido* alas;
		Barrido* base;
};

#endif
