#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "texture.h"
#include "brazo.h" 
#include "model_object.h"
#include "prisma.h"
#include "material_textura_suciedad_specular.h"
#include "material_color_solido.h"

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

		void girar_brazo(float angulo);
		void longitud_cable(float delta);
		void suciedad(float _suciedad);
	private:
		void actualizar_matrices_brazo();

		MaterialColorSolido material_gancho;
		MaterialColorSolido material_contrapeso;

		ModelObject mo_cubo;
		ModelObject mo_contra_peso;
		ModelObject mo_cable;
		ModelObject mo_gancho;
		ModelObject mo_brazo;

		CuboTexturado cubo;
		MaterialTexturaSuciedadSpecular material;
		CuboTexturado contra_peso;
		CuboTexturado cable;
		Prisma gancho;
		Brazo brazo;

		float angulo_brazo;
		float _longitud_cable;

		Texture textura_cabina;
		Texture mapa_suciedad;
		Texture mapa_specular;
};

#endif
